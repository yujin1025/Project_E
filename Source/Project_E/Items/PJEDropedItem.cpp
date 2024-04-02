// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PJEDropedItem.h"

// Delete later
#include "Character/PJECharacterPlayer.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

APJEDropedItem::APJEDropedItem()
{
	
}

void APJEDropedItem::SetItemCode(int32 NewItemCode)
{
	ItemCode = NewItemCode;
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
	}
	Destroy();
}