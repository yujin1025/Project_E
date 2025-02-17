﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../UI/CatInventoryWidget.h"
#include "../Items/Inventory.h"
#include "../Items/DropItem.h"
#include "Animation/AnimMontage.h"
#include "Projectile/CatWeapon.h"
#include "Component/HealthComponent.h"

APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bIsJumping)
    {
        JumpAttacking();
    }
}

void APJECharacterCat::InitWidget()
{
    Super::InitWidget();

    CatInventoryWidget = CreateWidget<UCatInventoryWidget>(GetWorld(), CatInventoryClass);
    if (CatInventoryWidget)
    {
        CatInventoryWidget->AddToViewport();
    }
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Triggered, this, &APJECharacterCat::Swing);
    }
}


void APJECharacterCat::BeginPlay()
{
    Super::BeginPlay();

    Inventory = NewObject<UInventory>(this);
    ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/CatItem.CatItem"));
}


bool APJECharacterCat::Grab()
{
    if (EquippedWeapon != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon is already equipped"));
        return false;
    }

    Server_Grab();
    return true;
}

ACatWeapon* APJECharacterCat::GetEquippedWeapon() const
{
    return EquippedWeapon;
}

void APJECharacterCat::Server_Grab_Implementation()
{
    if(Inventory)
    {
        UItem* NewItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (NewItem)
        {
            Inventory->AddItem(NewItem, false);

            Multicast_UpdateInventory(NewItem->ItemCode);

            if (NewItem->CatWeaponClass)
            {
                auto SpawnedWeapon = GetWorld()->SpawnActor<ACatWeapon>(NewItem->CatWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);

                if (SpawnedWeapon)
                {
                    SpawnedWeapon->SetDamage(NewItem->CatDamage);
                    EquippedWeapon = SpawnedWeapon;

                    Multicast_GrabWeapon(SpawnedWeapon);
                }
            }
        }
    }
}

bool APJECharacterCat::Server_Grab_Validate()
{
    return true;
}

void APJECharacterCat::Multicast_UpdateInventory_Implementation(int32 ItemID)
{
    if (CatInventoryWidget)
    {
        UItem* NewItem = UItem::SetItem(ItemDatabase, ItemID);
        if (NewItem)
        {
            CatInventoryWidget->UpdateInventory(NewItem);
        }
    }
}

void APJECharacterCat::Multicast_GrabWeapon_Implementation(ACatWeapon* Weapon)
{
    if (Weapon)
    {
        FName WeaponSocketName(TEXT("WeaponSocket"));
        FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
        Weapon->AttachToComponent(GetMesh(), AttachmentRules, WeaponSocketName);

        EquippedWeapon = Weapon;
    }
}



void APJECharacterCat::DropItem()
{
    Server_DropItem();
}

void APJECharacterCat::Server_DropItem_Implementation()
{
    Super::DropItem();

    if (Inventory)
    {
        UItem* CurrentItem = Inventory->GetCatInventoryItem();
        if (CurrentItem)
        {
            Inventory->RemoveItem(CurrentItem, false);

            Multicast_DropInventory(nullptr);

            FVector StartLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
            FVector EndLocation = StartLocation - FVector(0.0f, 0.0f, 500.0f);

            FHitResult HitResult;
            FCollisionQueryParams CollisionParams;
            CollisionParams.AddIgnoredActor(this);

            bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

            FVector DropLocation = bHit ? HitResult.ImpactPoint : StartLocation;
            FRotator DropRotation = GetActorRotation();

            ADropItem* DroppedItem = GetWorld()->SpawnActor<ADropItem>(CurrentItem->DropItmeClass, DropLocation, DropRotation);
            
            if (EquippedWeapon)
            {
                EquippedWeapon->Destroy();
            }
            EquippedWeapon = nullptr;
        }
    }
}

void APJECharacterCat::Multicast_DropInventory_Implementation(UItem* Item)
{
    if (CatInventoryWidget)
    {
        CatInventoryWidget->UpdateInventory(Item);
    }
}


void APJECharacterCat::DoubleJump()
{
    Super::DoubleJump();

    bIsJumping = true;
}

void APJECharacterCat::JumpAttacking()
{
    if (HasAuthority())
    {
        Server_DoubleJumpAttack();
    }
    else
    {
        Server_DoubleJumpAttack_Implementation();
    }
}


void APJECharacterCat::Server_DoubleJumpAttack_Implementation()
{
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(0.0f, 0.0f, -85.0f);

    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    if (bHit)
    {
        if (APJECharacterBase* TargetCharacter = Cast<APJECharacterBase>(HitResult.GetActor()))
        {
            if (UHealthComponent* TargetHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>())
            {
                TargetHealthComponent->ChangeHealth(-40);
            }
        }
    }
}


void APJECharacterCat::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);

    bIsJumping = false;
}


void APJECharacterCat::Dash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= DashSpeed;
    }
}


void APJECharacterCat::Swing()
{
    if (bIsAttacking)
        return;

    if (SwingMontage)
    {
        bIsAttacking = true;
        if (HasAuthority())
        {
            Multicast_Swing();
        }
        else
        {
            Server_Swing();
        }
    }
}

void APJECharacterCat::Server_Swing_Implementation()
{
    Multicast_Swing();
}


void APJECharacterCat::Multicast_Swing_Implementation()
{
    if (SwingMontage)
    {
        PlayAnimMontage(SwingMontage);
    }
}

