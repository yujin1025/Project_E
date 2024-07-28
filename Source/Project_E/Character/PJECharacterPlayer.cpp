// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include <Interface/PJEGameInterface.h>
#include "Components/BoxComponent.h"
#include "Player/PJEPlayerController.h"
#include "../Game/PJEGameModeBase.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"


APJECharacterPlayer::APJECharacterPlayer()
{
    bReplicates = true;
    bAlwaysRelevant = true;
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InteractionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
    InteractionTrigger->SetupAttachment(RootComponent);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(RootComponent);

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI/WBP_DieMessage"));
    if (WidgetClass.Succeeded())
    {
        DieMessageWidgetClass = WidgetClass.Class;
        UE_LOG(LogTemp, Warning, TEXT("Widget class successfully loaded."));
    }
}

void APJECharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APJECharacterPlayer, JumpHeight);
}


void APJECharacterPlayer::BeginPlay()
{
    Super::BeginPlay();
    
    APJEPlayerController* PlayerController = Cast<APJEPlayerController>(Controller);
    if (PlayerController)
    {
        EnableInput(PlayerController);
    }
    
    APJECharacterBase* Character = Cast<APJECharacterBase>(GetOwner());
    if (Character == nullptr)
        return;
    
    ECharacterType Type = Character->GetCharacterType();
    
    auto* GameMode = Cast<APJEGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode == nullptr)
        return;
    
    auto* Data = GameMode->GetCharacterStat(CharacterType);
    if (Data == nullptr)
        return;
    
    GetCharacterMovement()->MaxWalkSpeed = Data->MoveSpeed;
}

void APJECharacterPlayer::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnMove);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnLook);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APJECharacterPlayer::DoubleJump);
    EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APJECharacterPlayer::Dash);
    EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &APJECharacterPlayer::StopDash);
    EnhancedInputComponent->BindAction(DropAction, ETriggerEvent::Started, this, &APJECharacterPlayer::DropItem);
    EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APJECharacterPlayer::OnInteractBegin);
    EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APJECharacterPlayer::OnInteractEnd);
}

void APJECharacterPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if(InteractableActor && this->IsLocallyControlled())
    {
        InteractableActor->HidePointWidget();
    }
    
    InteractableActor = GetClosestActor();
    
    if(InteractableActor && this->IsLocallyControlled())
    {
        InteractableActor->ShowPointWidget();
    }

    OnFalling();
}

FVector APJECharacterPlayer::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance)
{
    FVector CameraLocation;
    FRotator CameraRotation;

    if (Controller)
    {
        Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);
    }

    FVector Start = CameraLocation;
    FVector End = Start + (CameraRotation.Vector() * RayCastDistance);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, Channel, CollisionParams))
    {
        if (HitResult.GetActor() && HitResult.GetActor()->IsA<APJECharacterBase>())
        {
            APJECharacterBase* TargetCharacter = Cast<APJECharacterBase>(HitResult.GetActor());
            if (TargetCharacter && TargetCharacter->IsTarget)
            {
                return FVector(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, HitResult.ImpactPoint.Z);
            }
        }
    }

    return End;
}

void APJECharacterPlayer::SetCamLocationRotation(FVector TargetLocation, FRotator TargetRotation)
{
    OriginCamLocation = FollowCamera->GetComponentLocation();
    FollowCamera->SetWorldLocation(TargetLocation);
    OriginCamRotation = FollowCamera->GetComponentRotation();
    FollowCamera->SetWorldRotation(TargetRotation);
}

void APJECharacterPlayer::BackCamera()
{
    FollowCamera->SetWorldLocation(OriginCamLocation);
    FollowCamera->SetWorldRotation(OriginCamRotation);
}


void APJECharacterPlayer::SetDead()
{
    Super::SetDead();

     APlayerController* PlayerController = Cast<APJEPlayerController>(GetController());
     if (PlayerController)
     {
         DisableInput(PlayerController);
    
         IPJEGameInterface* ABGameMode = Cast<IPJEGameInterface>(GetWorld()->GetAuthGameMode());
         if (ABGameMode)
         {
             ABGameMode->OnPlayerDead(0/*PlayerNumber*/);
         }
     }
}



void APJECharacterPlayer::OnMove(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    Move(MovementVector);
}

void APJECharacterPlayer::OnLook(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    Look(LookAxisVector);
}


void APJECharacterPlayer::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    bFirstJump = true;
    JumpCount = 0;
}

void APJECharacterPlayer::DoubleJump()
{
    Server_DoubleJump();
}

void APJECharacterPlayer::Server_DoubleJump_Implementation()
{
    Multicast_DoubleJump();
}

void APJECharacterPlayer::Multicast_DoubleJump_Implementation()
{
    if (bFirstJump)
    {
        bFirstJump = false;
        JumpCount++;
        LaunchCharacter(FVector(0.0f, 0.0f, JumpHeight), false, true);
        return;
    }

    else if (!bFirstJump && JumpCount < 2)
    {
        UCharacterMovementComponent* PlayerMovement = GetCharacterMovement();
        if (PlayerMovement)
        {
            LaunchCharacter(FVector(0.0f, 0.0f, JumpHeight), false, true);
            JumpCount++;

        }
        return;
    }
}

void APJECharacterPlayer::Dash()
{
    Server_Dash();
}

void APJECharacterPlayer::Server_Dash_Implementation()
{
    Multicast_Dash();
}

void APJECharacterPlayer::Multicast_Dash_Implementation()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
    }
}

void APJECharacterPlayer::StopDash()
{
    Server_StopDash();
}

void APJECharacterPlayer::Server_StopDash_Implementation()
{
    Multicast_StopDash();
}

void APJECharacterPlayer::Multicast_StopDash_Implementation()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
    }
}


void APJECharacterPlayer::DropItem()
{
}

void APJECharacterPlayer::OnFalling()
{
    if (GetCharacterMovement()->IsFalling())
    {
        if (!bIsFalling)
        {
            FallingStartLocation = GetActorLocation();
            bIsFalling = true;
        }
        else
        {
            float HeightChange = FMath::Abs(GetActorLocation().Z - FallingStartLocation.Z);

            if (HeightChange >= 400.0f)
            {
                //SetDead();
                //UE_LOG(LogTemp, Warning, TEXT("Dead - Falling"));

                if (!bHasShownMessage)
                {
                    if (DieMessageWidgetClass)
                    {
                        DieMessageWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), DieMessageWidgetClass);
                        if (DieMessageWidgetInstance)
                        {
                            UGameViewportClient* GameViewport = GetWorld()->GetGameViewport();
                            if (GameViewport)
                            {
                                DieMessageWidgetInstance->AddToViewport();
                                bHasShownMessage = true;
                            }
                        }
                    }
                }
                
            }
        }
    }
    else
    {
        
        if (bIsFalling && DieMessageWidgetInstance)
        {
            DieMessageWidgetInstance->RemoveFromViewport();
            DieMessageWidgetInstance = nullptr;
            bHasShownMessage = false;
        }
        bIsFalling = false;
    }
}


void APJECharacterPlayer::OnInteractBegin()
{
    if(HasAuthority())
    {
        if(InteractableActor)
        {
            InteractableActor->InteractionKeyPressed(this);
        }
    }
    else
    {
        if(InteractableActor)
        {
            InteractableActor->SetOwner(this);
            ServerOnInteractBegin();
        }
    }
}

void APJECharacterPlayer::ServerOnInteractBegin_Implementation()
{
    if(InteractableActor)
    {
        InteractableActor->SetOwner(this);
        InteractableActor->InteractionKeyPressed(this);
    }
}

void APJECharacterPlayer::OnInteractEnd()
{
    if(HasAuthority())
    {
        if(InteractableActor)
        {
            InteractableActor->SetOwner(this);
            InteractableActor->InteractionKeyReleased(this);
            //InteractableActor->bIsInteracting = true;
        }
    }
    else
    {
        Server_OnInteractEnd();
    }
}
void APJECharacterPlayer::Server_OnInteractEnd_Implementation()
{
    if(InteractableActor)
    {
        InteractableActor->SetOwner(this);
        InteractableActor->InteractionKeyReleased(this);
        //InteractableActor->bIsInteracting = true;
    }
}


APJEInteractiveActor* APJECharacterPlayer::GetClosestActor()
{    
    TArray<AActor*> OverlappingActors;
    TArray<APJEInteractiveActor*> InteractableActors;
    APJEInteractiveActor* ClosestActor = nullptr;

    InteractionTrigger->GetOverlappingActors(OverlappingActors);
    
    for (auto CurrentActor : OverlappingActors)
    {
        APJEInteractiveActor* TempActor = Cast<APJEInteractiveActor>(CurrentActor);
        if(TempActor)
        {
            if(TempActor->bIsPlayerNearby && TempActor->bIsInteractAble) InteractableActors.Add(TempActor);
        }
    }

    if(InteractableActors.IsEmpty())
    {
        if(InteractableActor != nullptr)
        {
            // 더 좋은 방식을 생각해보자.
            //OnInteractEnd();
            return nullptr;
        }
        return nullptr;
    }

    ClosestActor = InteractableActors[0];

    for(auto CurrentActor : InteractableActors)
    {
        if(GetDistanceTo(CurrentActor) < GetDistanceTo(ClosestActor))
        {
            ClosestActor = CurrentActor;
        }
    }

    return ClosestActor;
}
