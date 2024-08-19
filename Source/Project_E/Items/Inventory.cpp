// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

UInventory::UInventory()
{
}

void UInventory::AddItem(UItem* Item, bool bIsDuck)
{
    if (!Item)
		return;

    if (bIsDuck)
    {
        if (Item->Type == EItemType::Weapon && DuckWeaponInventory.Num() < 6)
            DuckWeaponInventory.Add(Item);
        else
            DuckNonWeaponInventory.Add(Item);
    }
    else
    {
        SetCatInventoryItem(Item);
    }

	UE_LOG(LogTemp, Warning, TEXT("Added item: %s"), *Item->Name);
}

void UInventory::RemoveItem(UItem* Item, bool bIsDuck)
{
    if (!Item)
        return;

    auto RemoveItemFromInventory = [&](TArray<UItem*>& Inventory)
    {
        for (int32 i = 0; i < Inventory.Num(); ++i)
        {
            if (Inventory[i] && Inventory[i]->ItemCode == Item->ItemCode)
            {
                Inventory.RemoveAt(i);
                break;
            }
        }
    };


    if (bIsDuck)
    {
        if (Item->Type == EItemType::Weapon)
            RemoveItemFromInventory(DuckWeaponInventory);
        else
            RemoveItemFromInventory(DuckNonWeaponInventory);
    }
    else
    {
        if (CatInventoryItem == Item)
            CatInventoryItem = nullptr;
    }

    if (GEngine)
    {
        FString InventoryContents = TEXT("DuckWeaponInventory: ");
        for (UItem* InventoryItem : DuckWeaponInventory)
        {
            InventoryContents += InventoryItem->Name + TEXT(", ");
        }

        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, InventoryContents);
    }
}

UItem* UInventory::RemoveLastItem(bool bIsDuck)
{
    UItem* RemovedItem = nullptr;

    if (DuckWeaponInventory.Num() > 0)
    {
        RemovedItem = DuckWeaponInventory.Pop();
    }

    return RemovedItem;
}

void UInventory::SetCatInventoryItem(UItem* Item)
{
    CatInventoryItem = Item;
}

UItem* UInventory::GetCatInventoryItem() const
{
    return CatInventoryItem;
}
