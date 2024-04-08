// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "../Items/Item.h"
#include "Components/Image.h"

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
}