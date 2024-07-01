// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"
#include "../Items/Item.h"
#include "Components/Image.h"

void USlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

}

void USlotWidget::SetItem(UItem* Item)
{

    if (Item && Item->ItemImage)
    {
        ItemImage->SetBrushFromTexture(Item->ItemImage);
        ItemImage->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        ItemImage->SetBrushFromTexture(nullptr);
        ItemImage->SetVisibility(ESlateVisibility::Hidden);
    }
}


