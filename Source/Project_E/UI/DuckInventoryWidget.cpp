// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckInventoryWidget.h"
#include "SlotWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

void UDuckInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

    InventoryGrid = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("InventoryGrid")));
}

void UDuckInventoryWidget::UpdateInventory(const TArray<UItem*>& Items, bool bIsWeaponInventory)
{
    for (const UItem* Item : Items)
    {
        if (Item)
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 17.f, FColor::Red, FString::Printf(TEXT("Item in Items array: %s"), *Item->Name));
        }
    }

    int32 CurrentSlotCount = Slots.Num();
    int32 ItemCount = Items.Num();
    int32 SlotsToAdd = ItemCount - CurrentSlotCount;

    // 새 slot 추가
    for (int32 i = 0; i < SlotsToAdd; i++)
    {
        USlotWidget* NewSlot = CreateWidget<USlotWidget>(this, LoadClass<USlotWidget>(nullptr, TEXT("/Game/UI/WBP_Slot.WBP_Slot_C")));
        if (NewSlot)
        {
            Slots.Add(NewSlot);
            UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(NewSlot);
            if (GridSlot)
            {
                int32 Column = CurrentSlotCount + i; 
                GridSlot->SetColumn(Column);
            }
        }
    }
    
    // 기존 slot 업데이트
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

    //필요없는 slot 삭제
    for (int32 i = ItemCount; i < Slots.Num(); i++)
    {
        if (Slots.IsValidIndex(i))
        {
            Slots[i]->SetItem(nullptr);
        }
    }
}
