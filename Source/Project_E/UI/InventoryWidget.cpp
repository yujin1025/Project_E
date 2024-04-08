// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "SlotWidget.h"
#include "../Items/Item.h"
#include "Blueprint/WidgetTree.h"

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //인벤토리에 표시될 각 슬롯을 생성
    for (int32 i = 0; i < 9; ++i)
    {
        USlotWidget* NewSlot = CreateSlotWidget();
        SlotsPanel->AddChild(NewSlot);
        Slots.Add(NewSlot);
    }
}

USlotWidget* UInventoryWidget::CreateSlotWidget()
{
    //새로운 USlotWidget 인스턴스를 생성
    USlotWidget* NewSlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);
    UE_LOG(LogTemp, Warning, TEXT("CreateSlotWidget: Creating slot widget"));
    return NewSlot;
}

void UInventoryWidget::AddItemToSlot(UItem* Item)
{
    UE_LOG(LogTemp, Warning, TEXT("AddItemToSlot: Adding item to slot"));

    for (auto& CurrentSlot : Slots)
    {
        //해당 슬롯이 비어있으면 이미지 설정
        if (!CurrentSlot->IsOccupied())
        {
            SetItemImage(CurrentSlot, Item->ItemImage);
            break;
        }
    }
}

void UInventoryWidget::SetItemImage(USlotWidget* ItemSlot, UTexture2D* ItemImage)
{
    UE_LOG(LogTemp, Warning, TEXT("SetItemImage: Setting item image"));
    if (ItemSlot)
    {
        ItemSlot->SetItemImage(ItemImage);
    }
}
