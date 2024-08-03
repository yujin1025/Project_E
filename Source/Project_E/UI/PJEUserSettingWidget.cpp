// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEUserSettingWidget.h"
#include "Components/Button.h"
#include "UI/Manager/PJEUIManager.h"
#include "Character/PJECharacterCat.h"

void UPJEUserSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SystemButton)
	{
		SystemButton->OnClicked.AddDynamic(this, &UPJEUserSettingWidget::OnSystemButtonClicked);
	}

	if (SoundButton)
	{
		SoundButton->OnClicked.AddDynamic(this, &UPJEUserSettingWidget::OnSoundButtonClicked);
	}

	if (GuideButton)
	{
		GuideButton->OnClicked.AddDynamic(this, &UPJEUserSettingWidget::OnGuideButtonClicked);
	}

	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPJEUserSettingWidget::OnMainMenuButtonClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJEUserSettingWidget::OnBackButtonClicked);
	}
}

void UPJEUserSettingWidget::OnSystemButtonClicked()
{
	// �ý��� ���� �������� ��ȯ�ϴ� �ڵ�
	if (SystemSettingsWidgetClass)
	{
		if (!SystemSettingsWidget.IsValid())
		{
			SystemSettingsWidget = UPJEUIManager::GetInstance()->ShowPopupUI(GetWorld(), SystemSettingsWidgetClass);
		}
	}
}

void UPJEUserSettingWidget::OnSoundButtonClicked()
{
	if (AudioSettingWidgetClass)
	{
		if (!AudioSettingWidget.IsValid())
		{
			AudioSettingWidget = UPJEUIManager::GetInstance()->ShowPopupUI(GetWorld(), AudioSettingWidgetClass);
		}
	}
}

void UPJEUserSettingWidget::OnGuideButtonClicked()
{
	if (Cast<APJECharacterCat>(GetWorld()->GetFirstPlayerController()->GetPawn()) != NULL)
	{
		if (CatGuideWidgetClass)
		{
			if (!CatGuideWidget.IsValid())
			{
				CatGuideWidget = UPJEUIManager::GetInstance()->ShowPopupUI(GetWorld(), CatGuideWidgetClass);
			}
		}
	}
	else
	{
		if (DuckGuideWidgetClass)
		{
			if (!DuckGuideWidget.IsValid())
			{
				DuckGuideWidget = UPJEUIManager::GetInstance()->ShowPopupUI(GetWorld(), DuckGuideWidgetClass);
			}
		}
	}
}

void UPJEUserSettingWidget::OnMainMenuButtonClicked()
{
	// ���� ȭ������ ��ȯ�ϴ� �ڵ�
	UE_LOG(LogTemp, Warning, TEXT("Main Menu Button Clicked"));
}

void UPJEUserSettingWidget::OnBackButtonClicked()
{
	// ���� �������� ���ư��� �ڵ�
	UE_LOG(LogTemp, Warning, TEXT("Back Button Clicked"));
}
