// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
//#include "InputMappingContext.h"
#include <Interface/PJEGameInterface.h>

#include "Components/BoxComponent.h"
#include "Game/PJEGameModeBase.h"
#include "Gimmick/PJEInteractInterface.h"

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

void APJECharacterPlayer::GetItem(int32 ItemCode)
{
    // Please implement ^~^
	
    // a. ItemCode is the code assigned to each item.
    // b. When the player's GetItem() is executed on class DroppedItem, the ItemCode is passed by argument.
    // c. Return false if it is impossible to get the item ( ex) inventory is full )
    // d. Return true if the item can be picked up
}

void APJECharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        EnableInput(PlayerController);
    }

    InputComponent->BindAction("Interact", IE_Pressed, this, &APJECharacterPlayer::OnInteractBegin);
    InputComponent->BindAction("Interact", IE_Released, this, &APJECharacterPlayer::OnInteractEnd);
}

void APJECharacterPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    
    if(IPJEInteractInterface* ClosestInterface = GetClosestInterface())
    {
        if(Interface)
        {
            Interface->HideInteractWidget();
        }

        Interface = ClosestInterface;
        
        if(Interface)
        {
            Interface->ShowInteractWidget();
        }
    }
}

void APJECharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(FName("MoveForward"), this, &APJECharacterPlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APJECharacterPlayer::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APJECharacterPlayer::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &APJECharacterPlayer::LookUp);

    //if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        //EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJECharacterPlayer::OnMove);
    //}
}

void APJECharacterPlayer::OnInteractBegin()
{
    if(Interface)
    {
        Interface->BeginInteracting(Cast<AActor>(this));
    }
}

void APJECharacterPlayer::OnInteractEnd()
{
    if(Interface)
    {
        Interface->EndInteracting(Cast<AActor>(this));
    }
}

IPJEInteractInterface* APJECharacterPlayer::GetClosestInterface()
{
    TArray<AActor*> OverlappingActors;
    TArray<IPJEInteractInterface*> OverlappingInterfaces;
    IPJEInteractInterface* ClosestInterface = nullptr;
    
    Volume->GetOverlappingActors(OverlappingActors);

    for(auto CurrentActor:OverlappingActors)
    {
        if(IPJEInteractInterface* CInterface = Cast<IPJEInteractInterface>(CurrentActor))
        {
            OverlappingInterfaces.Add(CInterface);
        }
    }
    
    if(OverlappingInterfaces.IsEmpty())
    {
        if(Interface)
        {
            // 차후 코드 수정 매우 필요.. 지금은 하기 싫다
            Interface->HideInteractWidget();
            //Interface->BreakInteracting();
            Interface = nullptr;
        }
        return nullptr;
    }

    if(OverlappingInterfaces.IsValidIndex(0))
    {
        ClosestInterface = OverlappingInterfaces[0];
    }
    
    for(auto CurrentInterface:OverlappingInterfaces)
    {
        if(GetDistanceTo(Cast<AActor>(CurrentInterface)) <
            GetDistanceTo(Cast<AActor>(ClosestInterface)))
        {
            ClosestInterface = CurrentInterface;
        }
    }
    
    return ClosestInterface;
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

    // ���̸� �� �� �÷��̾� ĳ���ʹ� ����, isTarget�� �ǵ���
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

void APJECharacterPlayer::MoveForward(float Value)
{
    if (Controller != nullptr && Value != 0.f)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
        AddMovementInput(Direction, Value);
    }
}

void APJECharacterPlayer::MoveRight(float Value)
{
    if (Controller != nullptr && Value != 0.f)
    {
        const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
        AddMovementInput(Direction, Value);
    }
}

void APJECharacterPlayer::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void APJECharacterPlayer::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void APJECharacterPlayer::SetDead()
{
    Super::SetDead();
    APlayerController* PlayerController = Cast<APlayerController>(GetController());
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



void APJECharacterPlayer::ShowPopUI()
{
    FVector TargetPosition = GetTargetPosition(ECollisionChannel::ECC_GameTraceChannel1, 100.0f);

    //Ȱ��ȭ �˾� ��� 
    if (TargetPosition != FVector::ZeroVector)
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController)
        {
            IPJEGameInterface* ABGameMode = Cast<IPJEGameInterface>(GetWorld()->GetAuthGameMode());
            if (ABGameMode)
            {
                //ABGameMode->ShowPopupWidget();
            }
        }
    }
}

void APJECharacterPlayer::Attack()
{

}


void APJECharacterPlayer::TakeItem()
{
    //TODO : TakeItem
}