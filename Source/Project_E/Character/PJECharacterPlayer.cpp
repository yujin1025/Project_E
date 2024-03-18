// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//#include "InputMappingContext.h"
#include <Interface/PJEGameInterface.h>
#include "Game/PJEGameModeBase.h"

APJECharacterPlayer::APJECharacterPlayer()
{
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

void APJECharacterPlayer::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController)
    {
        EnableInput(PlayerController);
    }
}

void APJECharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
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

    // 레이를 쏠 때 플레이어 캐릭터는 무시, isTarget만 되도록
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

    //활성화 팝업 재생 
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