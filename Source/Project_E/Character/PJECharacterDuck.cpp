// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterDuck.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Game/PJEGameModeBase.h"

APJECharacterDuck::APJECharacterDuck()
{
}

void APJECharacterDuck::BeginPlay()
{
	Super::BeginPlay();

    auto* GameMode = Cast<APJEGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode == nullptr)
        return;

    auto* Data = GameMode->GetCharacterStat(ECharacterType::Duck);
    if (Data == nullptr)
        return;

    GetCharacterMovement()->MaxWalkSpeed = Data->MoveSpeed;
}

void APJECharacterDuck::Attack()
{
	Super::Attack();
}

void APJECharacterDuck::Swallow()
{
}

void APJECharacterDuck::Shoot()
{
}

void APJECharacterDuck::RapidFire()
{
}