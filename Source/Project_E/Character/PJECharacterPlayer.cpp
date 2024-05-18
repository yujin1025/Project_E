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

APJECharacterPlayer::APJECharacterPlayer()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(GetMesh());
    CameraBoom->TargetArmLength = 600.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
    Volume->SetupAttachment(RootComponent);
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

void APJECharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    //Inventory = NewObject<UInventory>(this);

    APJEPlayerController* PlayerController = Cast<APJEPlayerController>(GetController());
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

    Volume->OnComponentBeginOverlap.AddDynamic(this, &APJECharacterPlayer::OnOverlapBegin);
    Volume->OnComponentEndOverlap.AddDynamic(this, &APJECharacterPlayer::OnOverlapEnd);
}

void APJECharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APJEPlayerController* PlayerController = Cast<APJEPlayerController>(Controller))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
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

    if(Interface)
    {
        Interface->HideInteracPointWidget();
    }
    
    Interface = GetClosestInterface();
    
    if(Interface)
    {
        Interface->ShowInteractPointWidget();    
    }
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
    UE_LOG(LogTemp, Warning, TEXT("Move Camera"));

    // Save Original Position
    OrgLocation = FollowCamera->GetComponentLocation();
    OrgRotation = FollowCamera->GetComponentRotation();
    
    // Move Camera
     FollowCamera->SetWorldLocation(TargetLocation);
     FollowCamera->SetWorldRotation(TargetRotation);
}

void APJECharacterPlayer::BackCameraToPawn()
{
    UE_LOG(LogTemp, Warning, TEXT("Back Camera"));

    // Move Camera to Origin Position
    FollowCamera->SetWorldLocation(OrgLocation);
    FollowCamera->SetWorldRotation(OrgRotation);
}


void APJECharacterPlayer::SetDead()
{
    //Super::SetDead();

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
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
    }
}

void APJECharacterPlayer::StopDash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
    }
}

void APJECharacterPlayer::Grab()
{

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
    if (Interface)
    {
        Interface->BeginInteracting(Cast<AActor>(this));
    }
}

void APJECharacterPlayer::OnInteractEnd()
{
    if (Interface)
    {
        Interface->EndInteracting(Cast<AActor>(this));
    }
}

void APJECharacterPlayer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if(IPJEInteractInterface* OtherActorInterface = Cast<IPJEInteractInterface>(OtherActor))
    {
        // If Cast Succeed
        OtherActorInterface->ShowInteractWidget();
    }
}

void APJECharacterPlayer::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if(IPJEInteractInterface* OtherActorInterface = Cast<IPJEInteractInterface>(OtherActor))
    {
        // If Cast Succeed
        OtherActorInterface->HideInteractWidget();
    }
}

IPJEInteractInterface* APJECharacterPlayer::GetClosestInterface()
{
    TArray<AActor*> OverlappingActors;
    TArray<IPJEInteractInterface*> OverlappingInterfaces;
    IPJEInteractInterface* ClosestInterface = nullptr;

    Volume->GetOverlappingActors(OverlappingActors);

    for (auto CurrentActor : OverlappingActors)
    {
        if (IPJEInteractInterface* CInterface = Cast<IPJEInteractInterface>(CurrentActor))
        {
            OverlappingInterfaces.Add(CInterface);
        }
    }

    if (OverlappingInterfaces.IsEmpty())
    {
        return nullptr;
    }

    ClosestInterface = OverlappingInterfaces[0];

    for (auto CurrentInterface : OverlappingInterfaces)
    {
        if (GetDistanceTo(Cast<AActor>(CurrentInterface)) <
            GetDistanceTo(Cast<AActor>(ClosestInterface)))
        {
            ClosestInterface = CurrentInterface;
        }
    }

    return ClosestInterface;
}
