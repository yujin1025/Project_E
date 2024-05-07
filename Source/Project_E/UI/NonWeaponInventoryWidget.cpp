// Fill out your copyright notice in the Description page of Project Settings.


#include "NonWeaponInventoryWidget.h"
#include "../Items/Inventory.h"

void UNonWeaponInventoryWidget::UpdateInventory(const TArray<class UItem*>& Items)
{
	UInventory* Inventory = NewObject<UInventory>();
	TArray<UItem*>& NonWeaponItems = Inventory->NonWeaponInventory;

	Super::UpdateInventory(NonWeaponItems);
}
