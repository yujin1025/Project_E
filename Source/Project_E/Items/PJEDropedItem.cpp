// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PJEDropedItem.h"

// Delete later
#include "Character/PJECharacterPlayer.h"
#include "Components/WidgetComponent.h"

APJEDropedItem::APJEDropedItem()
{
	ItemMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	Widget->SetupAttachment(ItemMesh);
	
	PointWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Point Interaction Widget"));
	PointWidget->SetupAttachment(Widget);
}

void APJEDropedItem::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);
	PointWidget->SetVisibility(false);
}

void APJEDropedItem::BeginInteracting(const AActor* InteractActor)
{
	Super::BeginInteracting(InteractActor);
}

// Item acquisition occurs the moment the interaction key is released on the keyboard.
void APJEDropedItem::EndInteracting(const AActor* InteractActor)
{
	Super::EndInteracting(InteractActor);

	// To be modified later
	AActor* NCInteractActor = const_cast<AActor*>(InteractActor);
	if(APJECharacterPlayer* InteractCharacter = Cast<APJECharacterPlayer>(NCInteractActor))
	{
		InteractCharacter->GetItem(ItemCode);
		InteractCharacter->SetHandItemCode(ItemCode);
	}
	Destroy();
}

void APJEDropedItem::ShowInteractWidget()
{
	Super::ShowInteractWidget();

	Widget->SetVisibility(true);
}

void APJEDropedItem::HideInteractWidget()
{
	Super::HideInteractWidget();

	Widget->SetVisibility(false);
}

void APJEDropedItem::ShowInteractPointWidget()
{
	Super::ShowInteractPointWidget();

	PointWidget->SetVisibility(true);
}

void APJEDropedItem::HideInteracPointWidget()
{
	Super::HideInteracPointWidget();

	PointWidget->SetVisibility(false);
}
