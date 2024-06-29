// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../UI/CatInventoryWidget.h"

APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
     if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
         EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &APJECharacterCat::Grab);
         EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Triggered, this, &APJECharacterCat::Swing);
     }
}


void APJECharacterCat::BeginPlay()
{
    Super::BeginPlay();

    ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));

    CatInventoryWidget = CreateWidget<UCatInventoryWidget>(GetWorld(), CatInventoryClass);
    if (CatInventoryWidget)
    {
        CatInventoryWidget->AddToViewport();
    }
}


void APJECharacterCat::Grab()
{
    UItem* NewItem = UItem::SetItem(ItemDatabase, GetHandItemCode());
    if (CatInventoryWidget)
    {
        CatInventoryWidget->UpdateInventory(NewItem);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("InventoryWidget is nullptr"));
    }
}

void APJECharacterCat::Swing()
{
}

void APJECharacterCat::Dash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= DashSpeed;
    }
}
