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

// 아이템 획득은 키보드에서 상호작용 키가 Release 되는 순간에 발생한다.
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
