// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../UI/CatInventoryWidget.h"
#include "../Items/Inventory.h"
#include "Animation/AnimMontage.h"
#include "Projectile/CatWeapon.h"

APJECharacterCat::APJECharacterCat()
{
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

    CatInventoryWidget = CreateWidget<UCatInventoryWidget>(GetWorld(), CatInventoryClass);
    if (CatInventoryWidget)
    {
        CatInventoryWidget->AddToViewport();
    }
}


void APJECharacterCat::Grab()
{
    if (Inventory) 
    {
        UItem* NewItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
        if (NewItem)
        {
            Inventory->AddItem(NewItem, false);

            if (CatInventoryWidget)
            {
                CatInventoryWidget->UpdateInventory(NewItem);
            }

            if (NewItem->WeaponClass)
            {
                auto SpawnedWeapon = GetWorld()->SpawnActor<ACatWeapon>(NewItem->WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
                
                if (SpawnedWeapon)
                {
                    SpawnedWeapon->SetDamage(NewItem->CatDamage);

                    FName WeaponSocketName(TEXT("WeaponSocket"));
                    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
                    SpawnedWeapon->AttachToComponent(GetMesh(), AttachmentRules, WeaponSocketName);

                    EquippedWeapon = SpawnedWeapon;
                }
            }
        }
    }
}

void APJECharacterCat::DropItem()
{
    Super::DropItem();

    if (Inventory)
    {
        UItem* CurrentItem = Inventory->GetCatInventoryItem();
        if (CurrentItem)
        {
            Inventory->RemoveItem(CurrentItem, false);

            if (CatInventoryWidget)
            {
                CatInventoryWidget->UpdateInventory(nullptr);
            }

            TArray<AActor*> AttachedActors;
            GetAttachedActors(AttachedActors);
            for (AActor* Actor : AttachedActors)
            {
                if (ACatWeapon* Weapon = Cast<ACatWeapon>(Actor))
                {
                    Weapon->Destroy();
                    EquippedWeapon = nullptr;
                }
            }
        }
    }
}

void APJECharacterCat::Swing()
{
    if (bIsAttacking)
        return;

    if (SwingMontage)
    {
        bIsAttacking = true;
        PlayAnimMontage(SwingMontage);
    }
}

void APJECharacterCat::Dash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= DashSpeed;
    }
}


