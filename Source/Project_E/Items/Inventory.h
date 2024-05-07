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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<UItem*> WeaponInventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<UItem*> NonWeaponInventory;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(UItem* Item);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void RemoveItem(UItem* Item);

    //UFUNCTION(BlueprintCallable, Category = "Inventory")
    //bool IsFull() const;
};
