// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterDuck.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Game/PJEGameModeBase.h"
#include "../Items/Inventory.h"
#include "Projectile/PJEProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../UI/DuckInventoryWidget.h"
#include "../Items/Item.h"

APJECharacterDuck::APJECharacterDuck()
{
    bCanShoot = true;
    bCanRapidFire = true;
    bIsSwallowed = false;
    MagicBallCount = 0;
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

    WeaponInventoryWidget = CreateWidget<UDuckInventoryWidget>(GetWorld(), WeaponInventoryClass);
    if (WeaponInventoryWidget)
    {
        WeaponInventoryWidget->AddToViewport();
    }

    NonWeaponInventoryWidget = CreateWidget<UDuckInventoryWidget>(GetWorld(), NonWeaponInventoryClass);
    if (NonWeaponInventoryWidget)
    {
        NonWeaponInventoryWidget->AddToViewport();
    }
}


void APJECharacterDuck::Swallow()
{
    if (Inventory)// && !Inventory->IsFull())
    {
        SwallowedItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (SwallowedItem)
        {
            Inventory->AddItem(SwallowedItem, true);

            if (SwallowedItem->ItemCode == 1)
                MagicBallCount++;

            ApplySpeedReduction();
            LogInventory();
            UpdateInventoryWidget(SwallowedItem->Type);
        }
    }
}

void APJECharacterDuck::DropItem()
{
    Super::DropItem();

    if (Inventory)
    {
        if (SwallowedItem)
        {
            Inventory->RemoveItem(SwallowedItem, true);

            if (SwallowedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();
            LogInventory();
            UpdateInventoryWidget(SwallowedItem->Type);

            SwallowedItem = nullptr;
        }
    }
}


void APJECharacterDuck::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Shoot"));
    if (bCanShoot && Inventory->GetWeaponCount() > 0)
    {
        if (FireMontage)
        {
            PlayAnimMontage(FireMontage);
        }

        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        MuzzleRotation.Pitch += 30.0f;

        APJEProjectile* Projectile = GetWorld()->SpawnActor<APJEProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);

        UItem* RemovedItem = Inventory->RemoveLastItem(true);
        if (RemovedItem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);

            if (RemovedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();
            LogInventory();
            UpdateInventoryWidget(RemovedItem->Type);
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
        float FireInterval = 0.3f;
        RapidFireCount = 0;

        // 타이머 핸들 초기화
        GetWorldTimerManager().SetTimer(RapidFireTimerHandle, this, &APJECharacterDuck::SpawnRapidFireProjectile, FireInterval, true, 0.0f);

        // 발사 가능 상태 재설정 타이머 설정
        bCanRapidFire = false;
        GetWorldTimerManager().SetTimer(RapidFireDelayTimer, this, &APJECharacterDuck::ResetRapidFire, 1.0f, false);
    }
}

void APJECharacterDuck::SpawnRapidFireProjectile()
{
    if (RapidFireCount < 3 && Inventory->GetWeaponCount() > 0)
    {
        if (RapidFireMontage)
        {
            PlayAnimMontage(RapidFireMontage);
        }

        FVector CameraLocation;
        FRotator CameraRotation;
        GetActorEyesViewPoint(CameraLocation, CameraRotation);

        MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

        FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
        FRotator MuzzleRotation = CameraRotation;
        MuzzleRotation.Pitch += 30.0f;

        APJEProjectile* Projectile = GetWorld()->SpawnActor<APJEProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation);

        UItem* RemovedItem = Inventory->RemoveLastItem(true);
        if (RemovedItem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);

            if (RemovedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();
            LogInventory();
            UpdateInventoryWidget(RemovedItem->Type);
        }

        RapidFireCount++;

        // 모든 발사체를 발사한 경우 타이머 해제
        if (RapidFireCount >= 3)
        {
            GetWorldTimerManager().ClearTimer(RapidFireTimerHandle);
        }
    }
}

void APJECharacterDuck::ResetRapidFire()
{
    bCanRapidFire = true;
}

void APJECharacterDuck::ApplySpeedReduction()
{
    if (MagicBallCount > 0 && Inventory->GetInventoryCount() > 3)
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * SwallowedMultiplier;
        bIsSwallowed = true;
    }
    else if (Inventory->GetInventoryCount() > 5)
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * SwallowedMultiplier;
        bIsSwallowed = true;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
        bIsSwallowed = false;
    }

    UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f"), GetCharacterMovement()->MaxWalkSpeed);
}


void APJECharacterDuck::Dash()
{
    if (bIsWalking)
    {
        if (MagicBallCount > 0)
        {
            GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * DashMultiplier * SwallowedMultiplier;
        }
        else
        {
            GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * DashMultiplier;
        }
    }
}

//나중에 다 확인하고 지우기
void APJECharacterDuck::LogInventory()
{
    if (Inventory)
    {
        if (Inventory->DuckWeaponInventory.Num() > 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("Current Duck Weapon Inventory:"));
            for (UItem* Item : Inventory->DuckWeaponInventory)
            {
                UE_LOG(LogTemp, Warning, TEXT("%s"), *Item->Name);
            }
        }

        if (Inventory->DuckNonWeaponInventory.Num() > 0)
        {
            UE_LOG(LogTemp, Warning, TEXT("Current Duck Non-Weapon Inventory:"));
            for (UItem* Item : Inventory->DuckNonWeaponInventory)
            {
                UE_LOG(LogTemp, Warning, TEXT("%s"), *Item->Name);
            }
        }
    }
}

void APJECharacterDuck::UpdateInventoryWidget(EItemType ItemType)
{
    if (ItemType == EItemType::Weapon && WeaponInventoryWidget)
    {
        WeaponInventoryWidget->UpdateInventory(Inventory->DuckWeaponInventory, true);
    }
    else if (ItemType == EItemType::NonWeapon && NonWeaponInventoryWidget)
    {
        NonWeaponInventoryWidget->UpdateInventory(Inventory->DuckNonWeaponInventory, false);
    }
}

