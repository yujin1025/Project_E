// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "../Items/Item.h"
#include "Components/Image.h"

void USlotWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void USlotWidget::UpdateSlot(UItem* Item)
{
    if (Item)
    {
        ItemImage->SetBrushFromTexture(Item->ItemImage);
    }
    else
    {
        // 빈 슬롯일 경우 이미지와 텍스트를 비웁니다.
        ItemImage->SetBrushFromTexture(nullptr);
    }
}

/*
void USlotWidget::SetItemImage(UTexture2D* ItemImage)
{
    if (ItemImg && ItemImage)
    {
        ItemImg->SetBrushFromTexture(ItemImage);
        CurrentItemImage = ItemImage;
    }
}

bool USlotWidget::IsOccupied() const
{
    return CurrentItemImage != nullptr;
}*/