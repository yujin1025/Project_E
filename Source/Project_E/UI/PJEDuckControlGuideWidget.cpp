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
	// 환경설정 UI로 돌아가기
	UPJEUIManager::GetInstance()->RemovePopupWidget(GetWorld(), this);
}
