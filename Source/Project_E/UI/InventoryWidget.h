// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "InventoryWidget.generated.h"

class UItem;
class USlotWidget;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UPanelWidget* InventoryPanel;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class USlotWidget> SlotWidgetClass;

    UFUNCTION(BlueprintCallable)
    virtual void UpdateInventory(const TArray<class UItem*>& Items);
};
    /*
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UPanelWidget* SlotsPanel; // Assume SlotsPanel is a panel where slots will be added

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
    TSubclassOf<class USlotWidget> SlotWidgetClass; 

    TArray<class USlotWidget*> Slots; // Array to store SlotWidgets

    // Function to add item to slot
    UFUNCTION(BlueprintCallable)
    void AddItemToSlot(UItem* Item);

    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
    //int32 SlotIndex = 0;

protected:
    virtual void NativeConstruct() override;

private:
    // Function to create SlotWidget and add it to SlotsPanel
    USlotWidget* CreateSlotWidget();

    // Function to set item image to SlotWidget
    void SetItemImage(USlotWidget* Slot, UTexture2D* ItemImage);
    */

