// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/InventoryWidget.h"
#include "WeaponInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UWeaponInventoryWidget : public UInventoryWidget
{
	GENERATED_BODY()
	
protected:
	virtual void UpdateInventory(const TArray<class UItem*>& Items) override;
};
