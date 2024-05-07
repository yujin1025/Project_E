// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryWidget.h"
#include "SlotWidget.h"
#include "../Items/Inventory.h"

void UWeaponInventoryWidget::UpdateInventory(const TArray<class UItem*>& Items)
{
	UInventory* Inventory = NewObject<UInventory>();
	TArray<UItem*>& WeaponItems = Inventory->WeaponInventory;

	Super::UpdateInventory(WeaponItems);

    /*
    // 빈 슬롯을 추가하여 빈칸 6개를 유지합니다.
    const int32 MaxSlots = 6;
    const int32 NumEmptySlots = MaxSlots - Items.Num();
    for (int32 i = 0; i < NumEmptySlots; ++i)
    {
        USlotWidget* NewEmptySlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);
        if (NewEmptySlot)
        {
            NewEmptySlot->UpdateSlot(nullptr); // 빈 슬롯을 업데이트합니다.
            InventoryPanel->AddChild(NewEmptySlot); // 슬롯을 인벤토리 패널에 추가합니다.
        }
    }*/
}
