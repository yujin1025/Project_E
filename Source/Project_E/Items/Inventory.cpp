// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

void UInventory::AddItem(UItem* Item)
{
	Items.Add(Item);
	UE_LOG(LogTemp, Warning, TEXT("Added item: %s"), *Item->Name);
}

void UInventory::RemoveItem(UItem* Item)
{
	Items.Remove(Item);
	UE_LOG(LogTemp, Warning, TEXT("Removed item: %s"), *Item->Name);
}

bool UInventory::IsFull() const
{
	const int32 MaxCapacity = 9;
	int32 NumItems = Items.Num();

	if (NumItems >= MaxCapacity)
		return true;

	return false;
}
