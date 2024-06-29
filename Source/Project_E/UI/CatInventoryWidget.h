// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "../Items/Item.h"
#include "CatInventoryWidget.generated.h"

class USlotWidget;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UCatInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    void UpdateInventory(UItem* Item);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    USlotWidget* ItemSlot;
	
};
