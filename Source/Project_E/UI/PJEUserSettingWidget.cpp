// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEUserSettingWidget.h"
#include "Components/Button.h"

void UPJEUserSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// �� ��ư�� Ŭ�� �̺�Ʈ ���ε�
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
	// ���� ���� �������� ��ȯ�ϴ� �ڵ�
	UE_LOG(LogTemp, Warning, TEXT("Sound Button Clicked"));
}

void UPJEUserSettingWidget::OnGuideButtonClicked()
{
	// ���� �ȳ� �������� ��ȯ�ϴ� �ڵ�
	UE_LOG(LogTemp, Warning, TEXT("Guide Button Clicked"));
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
