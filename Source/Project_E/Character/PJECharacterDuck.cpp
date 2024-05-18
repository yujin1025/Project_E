// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterDuck.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Game/PJEGameModeBase.h"
#include "../Items/Inventory.h"


APJECharacterDuck::APJECharacterDuck()
{
    bCanShoot = true;
    bCanRapidFire = true;
}

void APJECharacterDuck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
    {
        EnhancedInputComponent->BindAction(SwallowAction, ETriggerEvent::Started, this, &APJECharacterDuck::Swallow);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APJECharacterDuck::Shoot);
        EnhancedInputComponent->BindAction(RapidFireAction, ETriggerEvent::Triggered, this, &APJECharacterDuck::RapidFire);
    }

}

void APJECharacterDuck::BeginPlay()
{
	Super::BeginPlay();

    Inventory = NewObject<UInventory>(this);
}


void APJECharacterDuck::Grab()
{
}

void APJECharacterDuck::Swallow()
{
    if (Inventory)// && !Inventory->IsFull())
    {
        UDataTable* ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));

        UItem* NewItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (NewItem)
        {
            Inventory->AddItem(NewItem);
        }
    }

}

void APJECharacterDuck::Shoot()
{
    UE_LOG(LogTemp, Warning, TEXT("Shoot"));
    if (bCanShoot && Inventory->GetWeaponCount() > 0)
    {
        UItem* RemovedItem = Inventory->RemoveLastItem();
        if (RemovedItem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);
        }

        bCanShoot = false;
        GetWorld()->GetTimerManager().SetTimer(ShootDelayTimer, this, &APJECharacterDuck::ResetShoot, 0.2f, false);
    }

}

void APJECharacterDuck::ResetShoot()
{
    bCanShoot = true;
}

void APJECharacterDuck::RapidFire(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("RapidFire"));
    if (bCanRapidFire && Inventory->GetWeaponCount() > 2)
    {
        for (int32 i = 0; i < 3; ++i)
        {
            UItem* RemovedItem = Inventory->RemoveLastItem();
            if (RemovedItem)
            {
                UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);
            }
        }

        bCanRapidFire = false;
        GetWorld()->GetTimerManager().SetTimer(RapidFireDelayTimer, this, &APJECharacterDuck::ResetRapidFire, 1.0f, false);
    }
}

void APJECharacterDuck::ResetRapidFire()
{
    bCanRapidFire = true;
}

