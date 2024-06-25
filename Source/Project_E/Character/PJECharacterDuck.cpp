// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterDuck.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Game/PJEGameModeBase.h"
#include "../Items/Inventory.h"
#include "Projectile/PJEProjectile.h"


APJECharacterDuck::APJECharacterDuck()
{
    bCanShoot = true;
    bCanRapidFire = true;
    bIsSwallowed = false;
}

void APJECharacterDuck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
    {
        EnhancedInputComponent->BindAction(SwallowAction, ETriggerEvent::Started, this, &APJECharacterDuck::Swallow);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APJECharacterDuck::Fire);
        EnhancedInputComponent->BindAction(RapidFireAction, ETriggerEvent::Triggered, this, &APJECharacterDuck::RapidFire);
    }

}

void APJECharacterDuck::BeginPlay()
{
	Super::BeginPlay();

    Inventory = NewObject<UInventory>(this);
    ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));
}


void APJECharacterDuck::Grab()
{
}

void APJECharacterDuck::Swallow()
{
    if (Inventory)// && !Inventory->IsFull())
    {
        UItem* NewItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (NewItem)
        {
            Inventory->AddItem(NewItem);

            if (Inventory->GetInventoryCount() > 5 || (NewItem->ItemCode == 1 && Inventory->GetInventoryCount() > 3))
            {
                GetCharacterMovement()->MaxWalkSpeed *= SwallowedSpeed;
                bIsSwallowed = true;
            }
        }
    }

}

void APJECharacterDuck::Fire()
{
    FVector Location = ProjectileSpawnPoint->GetComponentLocation();
    FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

    APJEProjectile* Projectile = GetWorld()->SpawnActor<APJEProjectile>(ProjectileClass, Location, Rotation);
    //Projectile->SetOwner(this);






    UE_LOG(LogTemp, Warning, TEXT("Shoot"));
    if (bCanShoot && Inventory->GetWeaponCount() > 0)
    {
        UItem* RemovedItem = Inventory->RemoveLastItem();
        if (RemovedItem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);

            if (RemovedItem->ItemCode == 1 && Inventory->GetInventoryCount() <= 5)
                ResetSpeed();
            else if (Inventory->GetInventoryCount() <= 3)
                ResetSpeed();
        }

        //if (UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, outVelocity, startLoc, targetLoc, GetWorld()->GetGravityZ(), arcValue))
        bCanShoot = false;
        GetWorld()->GetTimerManager().SetTimer(ShootDelayTimer, this, &APJECharacterDuck::ResetFire, 0.2f, false);
    }

}

void APJECharacterDuck::ResetFire()
{
    bCanShoot = true;
}

void APJECharacterDuck::RapidFire(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("RapidFire"));
    if (bCanRapidFire && Inventory->GetWeaponCount() > 2)
    {
        bool bHasMagicBall = false;

        for (int32 i = 0; i < 3; ++i)
        {
            UItem* RemovedItem = Inventory->RemoveLastItem();
            if (RemovedItem)
            {
                UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);

                if (RemovedItem->ItemCode == 1)
                    bHasMagicBall = true;
            }
        }

        if (bHasMagicBall && Inventory->GetInventoryCount() <= 5)
            ResetSpeed();
        else if (Inventory->GetInventoryCount() <= 3)
            ResetSpeed();

        bCanRapidFire = false;
        GetWorld()->GetTimerManager().SetTimer(RapidFireDelayTimer, this, &APJECharacterDuck::ResetRapidFire, 1.0f, false);
    }
}

void APJECharacterDuck::ResetRapidFire()
{
    bCanRapidFire = true;
}

void APJECharacterDuck::ResetSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed /= SwallowedSpeed;
    bIsSwallowed = false;
}

void APJECharacterDuck::Dash()
{
    if (bIsWalking)
    {
        if (bIsSwallowed) 
        {
            GetCharacterMovement()->MaxWalkSpeed *= (DashSpeed * SwallowedSpeed);
        }
        else 
        {
            GetCharacterMovement()->MaxWalkSpeed *= DashSpeed;
        }
    }
}
