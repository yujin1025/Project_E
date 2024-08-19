// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJECatControlGuideWidget.h"
#include "Components/Button.h"
#include "UI/Manager/PJEUIManager.h"

void UPJECatControlGuideWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJECatControlGuideWidget::OnBackButtonClicked);
	}
}

void UPJECatControlGuideWidget::OnBackButtonClicked()
{
	// ȯ�漳�� UI�� ���ư���
	UPJEUIManager::GetInstance()->RemovePopupWidget(GetWorld(), this);
}
