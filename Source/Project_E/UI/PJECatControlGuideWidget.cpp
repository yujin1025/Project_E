// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJECatControlGuideWidget.h"
#include "Components/Button.h"

void UPJECatControlGuideWidget::NativeConstruct()
{
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJECatControlGuideWidget::OnBackButtonClicked);
	}
}

void UPJECatControlGuideWidget::OnBackButtonClicked()
{
	// ȯ�漳�� UI�� ���ư���
	this->RemoveFromParent();
}
