// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PJEDropedItem.h"

// Delete later
#include "Character/PJECharacterPlayer.h"

APJEDropedItem::APJEDropedItem()
{
	ItemMesh->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

}

void APJEDropedItem::BeginPlay()
{
	Super::BeginPlay();
}

void APJEDropedItem::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);
}

void APJEDropedItem::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	if(Character)
	{
		Character->SetHandItemCode(ItemCode);
	}
	Destroy();
}

void APJEDropedItem::SetItemCode(int32 NewItemCode)
{
	ItemCode = NewItemCode;
}
