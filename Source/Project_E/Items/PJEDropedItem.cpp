// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PJEDropedItem.h"

// Delete later
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

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
	if(ATP_ThirdPersonCharacter* InteractCharacter = Cast<ATP_ThirdPersonCharacter>(NCInteractActor))
	{
		InteractCharacter->GetItem(ItemCode);
	}
	Destroy();
}
