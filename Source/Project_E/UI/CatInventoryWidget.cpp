// Fill out your copyright notice in the Description page of Project Settings.


#include "CatInventoryWidget.h"
#include "SlotWidget.h"

void UCatInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    ItemSlot = Cast<USlotWidget>(GetWidgetFromName(TEXT("ItemSlot")));
}

void UCatInventoryWidget::UpdateInventory(UItem* Item)
{
    if (ItemSlot)
    {
        ItemSlot->SetItem(Item);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ItemSlot is nullptr"));
    }
}
