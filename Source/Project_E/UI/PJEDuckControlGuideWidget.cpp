// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEDuckControlGuideWidget.h"
#include "Components/Button.h"

void UPJEDuckControlGuideWidget::NativeConstruct()
{
	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJEDuckControlGuideWidget::OnBackButtonClicked);
	}
}

void UPJEDuckControlGuideWidget::OnBackButtonClicked()
{
	// ȯ�漳�� UI�� ���ư���
	this->RemoveFromParent();
}
