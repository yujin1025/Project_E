// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "../Items/Item.h"
#include "DuckInventoryWidget.generated.h"

class USlotWidget;
class UUniformGridPanel;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UDuckInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void UpdateInventory(const TArray<UItem*>& Items, bool bIsWeaponInventory);

protected:
	TArray<USlotWidget*> Slots;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUniformGridPanel* InventoryGrid;

	static const int32 MaxWeaponSlots = 6;
};
