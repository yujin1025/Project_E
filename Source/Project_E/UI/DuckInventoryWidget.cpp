// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckInventoryWidget.h"
#include "SlotWidget.h"
#include "Components/UniformGridPanel.h"

void UDuckInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    InventoryGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("InventoryGrid")));
}

void UDuckInventoryWidget::UpdateInventory(const TArray<UItem*>& Items, bool bIsWeaponInventory)
{
    int32 CurrentSlotCount = Slots.Num();
    int32 ItemCount = Items.Num();
    int32 SlotsToAdd = ItemCount - CurrentSlotCount;

    for (int32 i = 0; i < SlotsToAdd; i++)
    {
        USlotWidget* NewSlot = CreateWidget<USlotWidget>(this, LoadClass<USlotWidget>(nullptr, TEXT("/Game/UI/WBP_Slot.WBP_Slot_C")));
        if (NewSlot)
        {
            Slots.Add(NewSlot);
            InventoryGrid->AddChildToUniformGrid(NewSlot);
        }
    }
    
    for (int32 i = 0; i < Items.Num(); i++)
    {
        if (Slots.IsValidIndex(i) && Items.IsValidIndex(i))
        {
            Slots[i]->SetItem(Items[i]); 
            UE_LOG(LogTemp, Log, TEXT("Slot %d set with Item %s"), i, *Items[i]->Name);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Invalid Index: Slot %d or Item %d"), i, i);
        }
    }

    for (int32 i = ItemCount; i < Slots.Num(); i++)
    {
        if (Slots.IsValidIndex(i))
        {
            Slots[i]->SetItem(nullptr);
        }
    }
}
