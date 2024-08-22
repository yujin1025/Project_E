// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

UItem::UItem()
{
}

UItem* UItem::SetItem(const UDataTable* ItemDataTable, int32 Code)
{
    if (!ItemDataTable)
        return nullptr;

    FItemData* ItemData = ItemDataTable->FindRow<FItemData>(FName(FString::FromInt(Code)), TEXT(""));

    if (ItemData)
    {
        UItem* NewItem = NewObject<UItem>();
        if (NewItem)
        {
            NewItem->ItemCode = ItemData->ItemCode;
            NewItem->Name = ItemData->Name;
            NewItem->Type = ItemData->Type;
            NewItem->Weight = ItemData->Weight;
            NewItem->CatDamage = ItemData->CatDamage;
            NewItem->DuckDamage = ItemData->DuckDamage;
            NewItem->ItemImage = ItemData->ItemImage;
            NewItem->CatWeaponClass = ItemData->CatWeaponClass;
            NewItem->DuckWeaponClass = ItemData->DuckWeaponClass;
            NewItem->DropItmeClass = ItemData->DropItmeClass;
            
            UE_LOG(LogTemp, Warning, TEXT("Item loaded successfully: %s"), *NewItem->Name);
            return NewItem;
        }
    }

	return nullptr;
}

