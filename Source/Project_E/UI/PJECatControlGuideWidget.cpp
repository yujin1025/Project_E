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
	// 환경설정 UI로 돌아가기
	this->RemoveFromParent();
}
