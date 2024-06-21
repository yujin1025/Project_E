// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "../Items/Inventory.h"
#include "../UI/InventoryWidget.h"
#include <Interface/PJEGameInterface.h>
#include "Components/BoxComponent.h"
#include "Gimmick/PJEInteractInterface.h"
#include "Player/PJEPlayerController.h"
#include "../Game/PJEGameModeBase.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"

APJECharacterPlayer::APJECharacterPlayer()
{
    bReplicates = true;
    
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    InteractionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
    InteractionTrigger->SetupAttachment(RootComponent);

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


bool APJECharacterPlayer::GetItem(int32 ItemCode)
{
    /*
    if (Inventory && !Inventory->IsFull())
    {
        UDataTable* ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));

        UItem* NewItem = UItem::SetItem(ItemDatabase, ItemCode); 
        if (NewItem)
        {
            Inventory->AddItem(NewItem);
            //InventoryWidget->AddItemToSlot(NewItem);
            return true;
        }
    }*/

    return false;
}

void APJECharacterPlayer::BeginPlay() // 문제 없음
{
    Super::BeginPlay();

    //Inventory = NewObject<UInventory>(this);
    
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

void APJECharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) //의심됨
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APJEPlayerController* PlayerController = Cast<APJEPlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            //Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(DefaultContext, 1);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnMove);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnLook);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APJECharacterPlayer::DoubleJump);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APJECharacterPlayer::Dash);
        EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &APJECharacterPlayer::StopDash);
        //EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this, &APJECharacterPlayer::OpenInventory);
    }
    
    InputComponent->BindAction("Interact", IE_Pressed, this, &APJECharacterPlayer::OnInteractBegin);
    InputComponent->BindAction("Interact", IE_Released, this, &APJECharacterPlayer::OnInteractEnd);
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

void APJECharacterPlayer::MoveCameraToTarget(FVector TargetLocation, FRotator TargetRotation)
{
    // Save Original Position
    OrgLocation = FollowCamera->GetComponentLocation();
    OrgRotation = FollowCamera->GetComponentRotation();
    
    // Move Camera
     FollowCamera->SetWorldLocation(TargetLocation);
     FollowCamera->SetWorldRotation(TargetRotation);
}

void APJECharacterPlayer::BackCameraToPawn()
{
    // Move Camera to Origin Position
    FollowCamera->SetWorldLocation(OrgLocation);
    FollowCamera->SetWorldRotation(OrgRotation);
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

void APJECharacterPlayer::Grab()
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


/*
void APJECharacterPlayer::OpenInventory()
{
    if (InventoryWidgetInstance)
    {
        if (bIsInventoryOpen)
        {
            InventoryWidgetInstance->RemoveFromViewport();
            UE_LOG(LogTemp, Warning, TEXT("Inventory closed"));
        }
        else
        {
            InventoryWidgetInstance->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Inventory opened"));
        }
        bIsInventoryOpen = !bIsInventoryOpen;
    }
    else
    {
        if (InventoryWidgetClass)
        {
            InventoryWidgetInstance = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetClass);
            if (InventoryWidgetInstance)
            {
                InventoryWidgetInstance->AddToViewport();
                UE_LOG(LogTemp, Warning, TEXT("Inventory opened"));
                bIsInventoryOpen = true;
            }
        }
    }
}*/



void APJECharacterPlayer::OnInteractBegin()
{
    Server_OnInteractBegin();   
}
void APJECharacterPlayer::Server_OnInteractBegin_Implementation()
{
    Multicast_OnInteractBegin();
}
void APJECharacterPlayer::Multicast_OnInteractBegin_Implementation()
{
    if(InteractableActor)
    {
        InteractableActor->InteractionKeyPressed(this);
    }
}

void APJECharacterPlayer::OnInteractEnd()
{
    Server_OnInteractEnd();
}
void APJECharacterPlayer::Server_OnInteractEnd_Implementation()
{
    Multicast_OnInteractEnd();
}
void APJECharacterPlayer::Multicast_OnInteractEnd_Implementation()
{
    
    if(InteractableActor)
    {
        InteractableActor->InteractionKeyReleased(this);
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

    if(InteractableActors.IsEmpty()) return nullptr;

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
