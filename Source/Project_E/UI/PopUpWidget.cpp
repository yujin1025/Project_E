// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpWidget.h"
#include "UI/Manager/PJEUIManager.h"
#include <Kismet/GameplayStatics.h>

UPopUpWidget::UPopUpWidget()
{
    bIsFocusable = true;
}

void UPopUpWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UPopUpWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::One)
    {
        // ESC Ű�� ������ �� �ֻ�� ���� �ݱ�
        UPJEUIManager::GetInstance()->CloseTopmostPopupWidget(GetWorld());
        return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
    }

    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
