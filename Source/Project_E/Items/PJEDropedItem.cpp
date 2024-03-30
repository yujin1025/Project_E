// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PJEDropedItem.h"

// Delete later
#include "Character/PJECharacterPlayer.h"

APJEDropedItem::APJEDropedItem()
{
	
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