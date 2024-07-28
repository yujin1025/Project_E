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
	// 환경설정 UI로 돌아가기
	this->RemoveFromParent();
}
