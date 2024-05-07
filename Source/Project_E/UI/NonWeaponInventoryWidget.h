// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InventoryWidget.h"
#include "NonWeaponInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UNonWeaponInventoryWidget : public UInventoryWidget
{
	GENERATED_BODY()

protected:
	virtual void UpdateInventory(const TArray<class UItem*>& Items) override;
	
};
