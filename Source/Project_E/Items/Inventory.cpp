// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::AddItem(UItem* Item)
{
	Items.Add(Item);
}

void UInventory::RemoveItem(UItem* Item)
{
	Items.Remove(Item);
}
