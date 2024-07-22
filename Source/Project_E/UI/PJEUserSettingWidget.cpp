// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEUserSettingWidget.h"
#include "Components/Button.h"

void UPJEUserSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 각 버튼에 클릭 이벤트 바인딩
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
	// 시스템 설정 페이지로 전환하는 코드
	if (SystemSettingsWidgetClass)
	{
		if (!SystemSettingsWidget)
		{
			SystemSettingsWidget = CreateWidget<UUserWidget>(GetWorld(), SystemSettingsWidgetClass);
		}

		if (SystemSettingsWidget)
		{
			SystemSettingsWidget->AddToViewport();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("System Button Clicked"));
}

void UPJEUserSettingWidget::OnSoundButtonClicked()
{
	// 음향 설정 페이지로 전환하는 코드
	UE_LOG(LogTemp, Warning, TEXT("Sound Button Clicked"));
}

void UPJEUserSettingWidget::OnGuideButtonClicked()
{
	// 조작 안내 페이지로 전환하는 코드
	UE_LOG(LogTemp, Warning, TEXT("Guide Button Clicked"));
}

void UPJEUserSettingWidget::OnMainMenuButtonClicked()
{
	// 메인 화면으로 전환하는 코드
	UE_LOG(LogTemp, Warning, TEXT("Main Menu Button Clicked"));
}

void UPJEUserSettingWidget::OnBackButtonClicked()
{
	// 이전 페이지로 돌아가는 코드
	UE_LOG(LogTemp, Warning, TEXT("Back Button Clicked"));
}
