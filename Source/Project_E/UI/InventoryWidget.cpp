// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "SlotWidget.h"
#include "../Items/Item.h"
#include "Blueprint/WidgetTree.h"

void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UInventoryWidget::UpdateInventory(const TArray<class UItem*>& Items)
{
    // ������ ������ ������ ��� �����մϴ�.
    InventoryPanel->ClearChildren();

    // �ֱٿ� ȹ���� �������� ���� �������� ���ĵǵ��� �ε����� �������� ��ȸ�մϴ�.
    for (int32 i = Items.Num() - 1; i >= 0; --i)
    {
        UItem* Item = Items[i];
        USlotWidget* NewSlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);
        if (NewSlot)
        {
            NewSlot->UpdateSlot(Item);
            InventoryPanel->AddChild(NewSlot);
        }
    }
}
/*
void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    //�κ��丮�� ǥ�õ� �� ������ ����
    for (int32 i = 0; i < 9; ++i)
    {
        USlotWidget* NewSlot = CreateSlotWidget();
        if (NewSlot)
        {
            SlotsPanel->AddChild(NewSlot);
            Slots.Add(NewSlot);
            UE_LOG(LogTemp, Error, TEXT("CreateSlotWidget Add!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("CreateSlotWidget returned nullptr!"));
        }
    }

    // ���� �迭�� �߰��� ���� ���� ���
    UE_LOG(LogTemp, Warning, TEXT("Slots in inventory:"));
    for (int32 Index = 0; Index < Slots.Num(); ++Index)
    {
        UE_LOG(LogTemp, Warning, TEXT("Slot %d: %s"), Index, Slots[Index] ? TEXT("Valid") : TEXT("Invalid"));
    }
}

USlotWidget* UInventoryWidget::CreateSlotWidget()
{
    //���ο� USlotWidget �ν��Ͻ��� ����
    USlotWidget* NewSlot = CreateWidget<USlotWidget>(GetWorld(), SlotWidgetClass);
    UE_LOG(LogTemp, Warning, TEXT("CreateSlotWidget: Creating slot widget"));
    return NewSlot;
}

void UInventoryWidget::AddItemToSlot(UItem* Item)
{
    UE_LOG(LogTemp, Warning, TEXT("AddItemToSlot: Adding item to slot"));

    for (int32 Index = 0; Index < Slots.Num(); ++Index)
    {
        //�ش� ������ ���������
        if (!Slots[Index]->IsOccupied())
        {
            SetItemImage(Slots[Index], Item->ItemImage);
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
*/
