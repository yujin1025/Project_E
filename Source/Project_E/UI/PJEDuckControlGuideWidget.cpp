// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEDuckControlGuideWidget.h"
#include "Components/Button.h"
#include "UI/Manager/PJEUIManager.h"

void UPJEDuckControlGuideWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJEDuckControlGuideWidget::OnBackButtonClicked);
	}
}

void UPJEDuckControlGuideWidget::OnBackButtonClicked()
{
	// ȯ�漳�� UI�� ���ư���
	UPJEUIManager::GetInstance()->RemovePopupWidget(GetWorld(), this);
}
