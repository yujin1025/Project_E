#include "UI/PJEAudioSetting.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"

void UPJEAudioSetting::NativeConstruct()
{
	Super::NativeConstruct();

	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnMasterVolumeChanged);
	}

	if (BGMVolumeSlider)
	{
		BGMVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnBGMVolumeChanged);
	}

	if (EnvironmentVolumeSlider)
	{
		EnvironmentVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnEnvironmentVolumeChanged);
	}

	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnSFXVolumeChanged);
	}

	if (NarrationVolumeSlider)
	{
		NarrationVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnNarrationVolumeChanged);
	}

	if (VoiceChatVolumeSlider)
	{
		VoiceChatVolumeSlider->OnValueChanged.AddDynamic(this, &UPJEAudioSetting::OnVoiceChatVolumeChanged);
	}

	if (MasterVolumeSlider) MasterVolumeSlider->SetValue(0.5f);
	if (BGMVolumeSlider) BGMVolumeSlider->SetValue(0.5f);
	if (EnvironmentVolumeSlider) EnvironmentVolumeSlider->SetValue(0.5f);
	if (SFXVolumeSlider) SFXVolumeSlider->SetValue(0.5f);
	if (NarrationVolumeSlider) NarrationVolumeSlider->SetValue(0.5f);
	if (VoiceChatVolumeSlider) VoiceChatVolumeSlider->SetValue(0.5f);

	if (SpeakerComboBox)
	{
		SpeakerComboBox->OnSelectionChanged.AddDynamic(this, &UPJEAudioSetting::OnSpeakerSelectionChanged);
		SpeakerComboBox->AddOption(TEXT("Default"));
		SpeakerComboBox->AddOption(TEXT("Speaker"));
		SpeakerComboBox->AddOption(TEXT("Headphones"));
		SpeakerComboBox->SetSelectedIndex(0);
	}

	if (MicModeComboBox)
	{
		MicModeComboBox->OnSelectionChanged.AddDynamic(this, &UPJEAudioSetting::OnMicModeSelectionChanged);
		MicModeComboBox->AddOption(TEXT("Voice Detection"));
		MicModeComboBox->AddOption(TEXT("Push to Talk"));
		MicModeComboBox->SetSelectedIndex(0);
	}

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UPJEAudioSetting::OnResetButtonClicked);
	}

	if (BackButton)
	{
		BackButton->OnClicked.AddDynamic(this, &UPJEAudioSetting::OnBackButtonClicked);
	}
}

void UPJEAudioSetting::OnMasterVolumeChanged(float Value)
{
	SetVolume(MasterSoundClass, Value);
}

void UPJEAudioSetting::OnBGMVolumeChanged(float Value)
{
	SetVolume(BGMSoundClass, Value);
}

void UPJEAudioSetting::OnEnvironmentVolumeChanged(float Value)
{
	SetVolume(EnvironmentSoundClass, Value);
}

void UPJEAudioSetting::OnSFXVolumeChanged(float Value)
{
	SetVolume(SFXSoundClass, Value);
}

void UPJEAudioSetting::OnNarrationVolumeChanged(float Value)
{
	SetVolume(NarrationSoundClass, Value);
}

void UPJEAudioSetting::OnVoiceChatVolumeChanged(float Value)
{
	SetVolume(VoiceChatSoundClass, Value);
}

void UPJEAudioSetting::OnSpeakerSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Speaker selection logic
}

void UPJEAudioSetting::OnMicModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Mic mode selection logic
}

void UPJEAudioSetting::OnResetButtonClicked()
{
	if (MasterVolumeSlider) MasterVolumeSlider->SetValue(0.5f);
	if (BGMVolumeSlider) BGMVolumeSlider->SetValue(0.5f);
	if (EnvironmentVolumeSlider) EnvironmentVolumeSlider->SetValue(0.5f);
	if (SFXVolumeSlider) SFXVolumeSlider->SetValue(0.5f);
	if (NarrationVolumeSlider) NarrationVolumeSlider->SetValue(0.5f);
	if (VoiceChatVolumeSlider) VoiceChatVolumeSlider->SetValue(0.5f);
	if (SpeakerComboBox) SpeakerComboBox->SetSelectedIndex(0);
	if (MicModeComboBox) MicModeComboBox->SetSelectedIndex(0);
}

void UPJEAudioSetting::OnBackButtonClicked()
{
	// Return to previous menu
	this->RemoveFromParent();
}

void UPJEAudioSetting::SetVolume(USoundClass* SoundClass, float Value)
{
	if (SoundClass)
	{
		SoundClass->Properties.Volume = Value;
		UE_LOG(LogTemp, Log, TEXT("%s volume set to %f"), *SoundClass->GetName(), Value);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundClass is null!"));
	}
}
