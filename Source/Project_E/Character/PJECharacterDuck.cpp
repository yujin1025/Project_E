// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterDuck.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Game/PJEGameModeBase.h"
#include "../Items/Inventory.h"
#include "Projectile/DuckProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../UI/DuckInventoryWidget.h"
#include "../Items/Item.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


APJECharacterDuck::APJECharacterDuck()
{
    bCanShoot = true;
    bCanRapidFire = true;
    bIsSwallowed = false;
    bIsAiming = false;
    MagicBallCount = 0;
}


void APJECharacterDuck::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APJECharacterDuck::Fire);
        EnhancedInputComponent->BindAction(RapidFireAction, ETriggerEvent::Triggered, this, &APJECharacterDuck::RapidFire);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &APJECharacterDuck::EnterAimingMode);
        EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &APJECharacterDuck::ExitAimingMode);
    }
}

void APJECharacterDuck::InitWidget()
{
    Super::InitWidget();
    
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

void APJECharacterDuck::BeginPlay()
{
    Super::BeginPlay();

    SetOwner(GetController());

    Inventory = NewObject<UInventory>(this);
    ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/DuckItem.DuckItem"));
}

void APJECharacterDuck::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(GEngine) GEngine->AddOnScreenDebugMessage(12, 17.f, FColor::Red, FString::Printf(TEXT("Duck Live : %f"), DeltaTime));

    if (bIsAiming)
    {
        FRotator CameraRotation = GetControlRotation();
        FRotator NewRotation(0.0f, CameraRotation.Yaw, 0.0f);
        SetActorRotation(NewRotation);

        CalculateProjectilePath();
    }
}

void APJECharacterDuck::Swallow()
{
    if (!bCanSwallow)
        return;

    Server_Swallow();
}

void APJECharacterDuck::Server_Swallow_Implementation()
{
    if (Inventory)
    {
        UItem* SwallowedItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (SwallowedItem)
        {
            Inventory->AddItem(SwallowedItem, true);
            SwallowedItems.Add(SwallowedItem);

            if (SwallowedItem->ItemCode == 1)
                MagicBallCount++;

            ApplySpeedReduction();
            Multicast_SwallowInventory(SwallowedItem->ItemCode);

            bCanSwallow = false;
            GetWorld()->GetTimerManager().SetTimer(SwallowCooldownTimer, this, &APJECharacterDuck::ResetSwallow, 0.2f, false);
        }
    }
}

void APJECharacterDuck::Multicast_SwallowInventory_Implementation(int32 ItemID)
{
    UItem* NewItem = UItem::SetItem(ItemDatabase, ItemID);
    if (NewItem)
    {
        if (!HasAuthority())
        {
            Inventory->AddItem(NewItem, true);
        }
        UpdateInventoryWidget(NewItem->Type);
    }
}


void APJECharacterDuck::ResetSwallow()
{
    bCanSwallow = true;
}

void APJECharacterDuck::DropItem()
{
    Super::DropItem();

    Server_DropItem();
}

void APJECharacterDuck::Server_DropItem_Implementation()
{
    if (Inventory)
    {
        if (SwallowedItems.Num() > 0)
        {
            UItem* SwallowedItem = SwallowedItems.Last();
            SwallowedItems.Remove(SwallowedItem);

            Inventory->RemoveItem(SwallowedItem, true);

            if (SwallowedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();
            Multicast_DropItem(SwallowedItem->ItemCode);

            SwallowedItem = nullptr;
        }
    }
}

void APJECharacterDuck::Multicast_DropItem_Implementation(int32 ItemID)
{
    UItem* NewItem = UItem::SetItem(ItemDatabase, ItemID);
    if (NewItem)
    {
        if (!HasAuthority())
        {
            Inventory->RemoveItem(NewItem, true);
        }
        UpdateInventoryWidget(NewItem->Type);
    }
}


void APJECharacterDuck::Fire()
{
    if (!bIsAiming)
        return;

    if (!HasAuthority())
    {
        if (bCanShoot && Inventory->GetWeaponCount() > 0)
        {
            UItem* RemovedItem = Inventory->RemoveLastItem(true);
            if (RemovedItem)
            {
                PredictedProjectile = GetWorld()->SpawnActor<ADuckProjectile>(RemovedItem->DuckWeaponClass, MuzzleLocation, MuzzleRotation);
            }
        }
    }

    Server_Fire(MuzzleLocation, MuzzleRotation);
}

void APJECharacterDuck::Server_Fire_Implementation(FVector ClientMuzzleLocation, FRotator ClientMuzzleRotation)
{
    if (bCanShoot && Inventory->GetWeaponCount() > 0)
    {
        UItem* RemovedItem = Inventory->RemoveLastItem(true);
        if (RemovedItem)
        {
            ADuckProjectile* Projectile = GetWorld()->SpawnActor<ADuckProjectile>(RemovedItem->DuckWeaponClass, ClientMuzzleLocation, ClientMuzzleRotation);

            if (RemovedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();

            Multicast_Fire(ClientMuzzleLocation, ClientMuzzleRotation);
            Multicast_DropItem(RemovedItem->ItemCode);
        }

        bCanShoot = false;
        GetWorld()->GetTimerManager().SetTimer(ShootDelayTimer, this, &APJECharacterDuck::ResetFire, 0.2f, false);
    }
}

void APJECharacterDuck::Multicast_Fire_Implementation(FVector Location, FRotator Rotation)
{
    if (FireMontage)
    {
        PlayAnimMontage(FireMontage);
    }

    if (!HasAuthority())
    {
        if (PredictedProjectile)
        {
            PredictedProjectile->Destroy();
            PredictedProjectile = nullptr;  
        }
    }
}



void APJECharacterDuck::ResetFire()
{
    bCanShoot = true;
}


void APJECharacterDuck::RapidFire(const FInputActionValue& Value)
{
    if (!bIsAiming)
        return;

    Server_RapidFire(MuzzleLocation, MuzzleRotation);
}

void APJECharacterDuck::Server_RapidFire_Implementation(FVector InMuzzleLocation, FRotator InMuzzleRotation)
{
    if (bCanRapidFire && Inventory->GetWeaponCount() > 2)
    {
        MuzzleLocation = InMuzzleLocation;
        MuzzleRotation = InMuzzleRotation;

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

        UItem* RemovedItem = Inventory->RemoveLastItem(true);
        if (RemovedItem)
        {
            UE_LOG(LogTemp, Warning, TEXT("Shot item: %s"), *RemovedItem->Name);

            ADuckProjectile* Projectile = GetWorld()->SpawnActor<ADuckProjectile>(RemovedItem->DuckWeaponClass, MuzzleLocation, MuzzleRotation);

            if (RemovedItem->ItemCode == 1)
            {
                MagicBallCount--;
                if (MagicBallCount < 0)
                    MagicBallCount = 0;
            }
            ApplySpeedReduction();
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
    float NewSpeed;
    bool bNewIsSwallowed;

    if (MagicBallCount > 0 && Inventory->GetInventoryCount() > 3)
    {
        NewSpeed = DefaultWalkSpeed * SwallowedMultiplier;
        bNewIsSwallowed = true;
    }
    else if (Inventory->GetInventoryCount() > 5)
    {
        NewSpeed = DefaultWalkSpeed * SwallowedMultiplier;
        bNewIsSwallowed = true;
    }
    else
    {
        NewSpeed = DefaultWalkSpeed;
        bNewIsSwallowed = false;
    }

    GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
    bIsSwallowed = bNewIsSwallowed;

    Multicast_UpdateSpeed(NewSpeed, bNewIsSwallowed);
}

void APJECharacterDuck::Multicast_UpdateSpeed_Implementation(float NewSpeed, bool bNewIsSwallowed)
{
    GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
    bIsSwallowed = bNewIsSwallowed;

    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 17.f, FColor::Blue, FString::Printf(TEXT("Updated Speed on Client: %f"), GetCharacterMovement()->MaxWalkSpeed));
}


void APJECharacterDuck::Dash()
{
    if (!bIsWalking)
        return;

    float SpeedMultiplier = bIsSwallowed ? DashMultiplier * SwallowedMultiplier : DashMultiplier;

    if (bIsAiming)
    {
        if (GetInputAxisValue("MoveForward") > 0.0f)
        {
            GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * SpeedMultiplier;
        }
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed * SpeedMultiplier;
    }
}

void APJECharacterDuck::UpdateInventoryWidget(EItemType ItemType)
{
    if (ItemType == EItemType::Weapon && WeaponInventoryWidget)
    {
        WeaponInventoryWidget->UpdateInventory(Inventory->DuckWeaponInventory, true);
        if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 17.f, FColor::Red, FString::Printf(TEXT("DuckWeaponInventory : %d"), Inventory->GetWeaponCount()));
    }
    else if (ItemType == EItemType::NonWeapon && NonWeaponInventoryWidget)
    {
        NonWeaponInventoryWidget->UpdateInventory(Inventory->DuckNonWeaponInventory, false);
    }
}

void APJECharacterDuck::EnterAimingMode()
{
    bIsAiming = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
}

void APJECharacterDuck::ExitAimingMode()
{
    bIsAiming = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APJECharacterDuck::CalculateProjectilePath()
{
    FVector CameraLocation;
    FRotator CameraRotation;
    GetActorEyesViewPoint(CameraLocation, CameraRotation);

    // 발사 위치 계산
    MuzzleOffset.Set(100.0f, 0.0f, 0.0f);
    MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
    MuzzleRotation = CameraRotation;
    MuzzleRotation.Pitch += 23.0f;

    // 예측 궤도 계산
    FPredictProjectilePathParams PredictParams(1.0f, MuzzleLocation, MuzzleRotation.Vector() * 1000.f, 10.f, ECC_Visibility, this);
    FPredictProjectilePathResult PredictResult;

    bool bHit = UGameplayStatics::PredictProjectilePath(this, PredictParams, PredictResult);

    FlushPersistentDebugLines(GetWorld());

    if (bHit && PredictResult.PathData.Num() > 0)
    {
        for (FPredictProjectilePathPointData PointData : PredictResult.PathData)
        {
            DrawDebugSphere(GetWorld(), PointData.Location, 5.f, 8, FColor::Green, false, 0.0f);
        }
    }
}

