// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Inventory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_E_API UInventory : public UObject
{
	GENERATED_BODY()
	
public:
    UInventory();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<UItem*> DuckWeaponInventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<UItem*> DuckNonWeaponInventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UItem* CatInventoryItem;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(UItem* Item, bool bIsDuck);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(UItem* Item, bool bIsDuck);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UItem* RemoveLastItem(bool bIsDuck);

    int32 GetWeaponCount() { return DuckWeaponInventory.Num(); }
    int32 GetNonWeaponCount() { return DuckNonWeaponInventory.Num(); }
    int32 GetInventoryCount() const { return DuckWeaponInventory.Num() + DuckNonWeaponInventory.Num(); }

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetCatInventoryItem(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    UItem* GetCatInventoryItem() const;
};
