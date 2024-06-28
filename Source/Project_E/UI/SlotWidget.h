// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "SlotWidget.generated.h"

class UImage;
//class UItem;
/**
 * 
 */
UCLASS()
class PROJECT_E_API USlotWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UImage* ItemImage;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetItem(UItem* Item);

};
