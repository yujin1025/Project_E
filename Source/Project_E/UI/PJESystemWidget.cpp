﻿#include "PJESystemWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/PostProcessVolume.h"
#include "EngineUtils.h" 
#include "PJEGameInstance.h"
#include "Project_E/PJESystemSettingsSaveGame.h"
#include "UI/Manager/PJEUIManager.h"

void UPJESystemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 포스트 프로세싱 볼륨 찾기
	for (TActorIterator<APostProcessVolume> It(GetWorld()); It; ++It)
	{
		PostProcessVolume = *It;
		if (PostProcessVolume->bUnbound)
		{
			break;
		}
	}
	PostProcessVolume->bUnbound = true;

	// 해상도 선택 초기값 설정
	if (ResolutionComboBox)
	{
		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UPJESystemWidget::OnResolutionChanged);
		ResolutionComboBox->AddOption(TEXT("1280x720"));
		ResolutionComboBox->AddOption(TEXT("1920x1080"));
		ResolutionComboBox->AddOption(TEXT("3440x1440"));
	}

	// 화면 모드 선택 초기값 설정
	if (ScreenModeComboBox)
	{
		ScreenModeComboBox->OnSelectionChanged.AddDynamic(this, &UPJESystemWidget::OnScreenModeChanged);
		ScreenModeComboBox->AddOption(TEXT("전체 화면"));
		ScreenModeComboBox->AddOption(TEXT("전체 창 화면"));
		ScreenModeComboBox->AddOption(TEXT("창 화면"));
	}

	// 슬라이더 초기값 설정
	if (CameraSpeedSlider)
	{
		CameraSpeedSlider->OnValueChanged.AddDynamic(this, &UPJESystemWidget::OnCameraSpeedChanged);
	}

	if (BrightnessSlider)
	{
		BrightnessSlider->OnValueChanged.AddDynamic(this, &UPJESystemWidget::OnBrightnessChanged);
	}

	// 버튼 이벤트 바인딩
	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UPJESystemWidget::OnResetButtonClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJESystemWidget::OnBackButtonClicked);
	}

	if (UGameplayStatics::DoesSaveGameExist(TEXT("SystemSettings"), 0))
	{
		LoadSettings();
	}
	else
	{
		ApplyDefaultSettings();
		SaveSettings();
	}
}

void UPJESystemWidget::OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// 해상도 변경 처리
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings)
	{
		if (SelectedItem == "1280x720")
		{
			UserSettings->SetScreenResolution(FIntPoint(1280, 720));
		}
		else if (SelectedItem == "1920x1080")
		{
			UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
		}
		else if (SelectedItem == "3440x1440")
		{
			UserSettings->SetScreenResolution(FIntPoint(3440, 1440));
		}
		UserSettings->ApplySettings(false);
		SaveSettings();
	}
}

void UPJESystemWidget::OnScreenModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// 화면 모드 변경 처리
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	if (UserSettings)
	{
		if (SelectedItem == "전체 화면")
		{
			UserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
		}
		else if (SelectedItem == "전체 창 화면")
		{
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		}
		else if (SelectedItem == "창 화면")
		{
			UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		}
		UserSettings->ApplySettings(false);
		SaveSettings();
	}
}

void UPJESystemWidget::OnCameraSpeedChanged(float Value)
{
	// 카메라 속도 변경 처리
	GameInstance = Cast<UPJEGameInstance>(GetGameInstance());
	GameInstance->SetCarmeraSpeed(Value);
	SaveSettings();
}

void UPJESystemWidget::OnBrightnessChanged(float Value)
{
	if (PostProcessVolume)
	{
		// 노출 설정
		PostProcessVolume->Settings.bOverride_AutoExposureMethod = true;
		PostProcessVolume->Settings.AutoExposureMethod = EAutoExposureMethod::AEM_Manual;
		PostProcessVolume->Settings.bOverride_AutoExposureBias = true;

		float ExposureBias = FMath::Lerp(-0.f, 20.0f, Value);
		PostProcessVolume->Settings.AutoExposureBias = ExposureBias;

		SaveSettings();
	}
}

void UPJESystemWidget::OnResetButtonClicked()
{
	// 모든 설정을 기본값으로 리셋
	if (ResolutionComboBox)
	{
		ResolutionComboBox->SetSelectedIndex(0);
		OnResolutionChanged(ResolutionComboBox->GetSelectedOption(), ESelectInfo::Direct);
	}
	if (ScreenModeComboBox)
	{
		ScreenModeComboBox->SetSelectedIndex(0);
		OnScreenModeChanged(ScreenModeComboBox->GetSelectedOption(), ESelectInfo::Direct);
	}
	if (CameraSpeedSlider)
	{
		CameraSpeedSlider->SetValue(0.5f);
		OnCameraSpeedChanged(0.5f);
	}
	if (BrightnessSlider)
	{
		BrightnessSlider->SetValue(0.5f);
		OnBrightnessChanged(0.5f);
	}

}

void UPJESystemWidget::OnBackButtonClicked()
{
	// 환경설정 UI로 돌아가기
	UPJEUIManager::GetInstance()->RemovePopupWidget(GetWorld(), this);
}

void UPJESystemWidget::SaveSettings()
{
	const FString SaveSlotName = TEXT("SystemSettings");
	const int32 UserIndex = 0;

	UPJESystemSettingsSaveGame* SaveGameInstance = Cast<UPJESystemSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UPJESystemSettingsSaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		if (ResolutionComboBox)
		{
			SaveGameInstance->Resolution = ResolutionComboBox->GetSelectedOption();
		}
		if (ScreenModeComboBox)
		{
			SaveGameInstance->ScreenMode = ScreenModeComboBox->GetSelectedOption();
		}
		if (CameraSpeedSlider)
		{
			SaveGameInstance->CameraSpeed = CameraSpeedSlider->GetValue();
		}
		if (BrightnessSlider)
		{
			SaveGameInstance->Brightness = BrightnessSlider->GetValue();
		}

		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
		{
			;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to save system settings."));
		}
	}
}

void UPJESystemWidget::LoadSettings()
{
	const FString SaveSlotName = TEXT("SystemSettings");
	const int32 UserIndex = 0;

	UPJESystemSettingsSaveGame* LoadGameInstance = Cast<UPJESystemSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

	if (LoadGameInstance)
	{
		if (ResolutionComboBox)
		{
			ResolutionComboBox->SetSelectedOption(LoadGameInstance->Resolution);
			OnResolutionChanged(LoadGameInstance->Resolution, ESelectInfo::Direct);
		}
		if (ScreenModeComboBox)
		{
			ScreenModeComboBox->SetSelectedOption(LoadGameInstance->ScreenMode);
			OnScreenModeChanged(LoadGameInstance->ScreenMode, ESelectInfo::Direct);
		}
		if (CameraSpeedSlider)
		{
			CameraSpeedSlider->SetValue(LoadGameInstance->CameraSpeed);
			OnCameraSpeedChanged(LoadGameInstance->CameraSpeed);
		}
		if (BrightnessSlider)
		{
			BrightnessSlider->SetValue(LoadGameInstance->Brightness);
			OnBrightnessChanged(LoadGameInstance->Brightness);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load system settings."));
	}
}

void UPJESystemWidget::ApplyDefaultSettings()
{
	if (ResolutionComboBox)
	{
		ResolutionComboBox->SetSelectedIndex(0);
		OnResolutionChanged(ResolutionComboBox->GetSelectedOption(), ESelectInfo::Direct);
	}
	if (ScreenModeComboBox)
	{
		ScreenModeComboBox->SetSelectedIndex(0);
		OnScreenModeChanged(ScreenModeComboBox->GetSelectedOption(), ESelectInfo::Direct);
	}
	if (CameraSpeedSlider)
	{
		CameraSpeedSlider->SetValue(0.5f);
		OnCameraSpeedChanged(0.5f);
	}
	if (BrightnessSlider)
	{
		BrightnessSlider->SetValue(0.5f);
		OnBrightnessChanged(0.5f);
	}
}
