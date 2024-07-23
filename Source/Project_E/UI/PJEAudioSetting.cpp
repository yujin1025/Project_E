// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEAudioSetting.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"

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

	if (SpeakerComboBox)
	{
		SpeakerComboBox->OnSelectionChanged.AddDynamic(this, &UPJEAudioSetting::OnSpeakerSelectionChanged);
	}

	if (MicModeComboBox)
	{
		MicModeComboBox->OnSelectionChanged.AddDynamic(this, &UPJEAudioSetting::OnMicModeSelectionChanged);
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
	// Master Volume ���� ����
}

void UPJEAudioSetting::OnBGMVolumeChanged(float Value)
{
	// BGM Volume ���� ����
}

void UPJEAudioSetting::OnEnvironmentVolumeChanged(float Value)
{
	// Environment Volume ���� ����
}

void UPJEAudioSetting::OnSFXVolumeChanged(float Value)
{
	// SFX Volume ���� ����
}

void UPJEAudioSetting::OnNarrationVolumeChanged(float Value)
{
	// Narration Volume ���� ����
}

void UPJEAudioSetting::OnVoiceChatVolumeChanged(float Value)
{
	// Voice Chat Volume ���� ����
}

void UPJEAudioSetting::OnSpeakerSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Speaker ���� ���� ����
}

void UPJEAudioSetting::OnMicModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	// Mic Mode ���� ���� ����
}

void UPJEAudioSetting::OnResetButtonClicked()
{
	// ��� ������ �⺻������ ����
	if (MasterVolumeSlider) MasterVolumeSlider->SetValue(0.5f);
	if (BGMVolumeSlider) BGMVolumeSlider->SetValue(0.5f);
	if (EnvironmentVolumeSlider) EnvironmentVolumeSlider->SetValue(0.5f);
	if (SFXVolumeSlider) SFXVolumeSlider->SetValue(0.5f);
	if (NarrationVolumeSlider) NarrationVolumeSlider->SetValue(0.5f);
	if (VoiceChatVolumeSlider) VoiceChatVolumeSlider->SetValue(0.5f);
	if (SpeakerComboBox) SpeakerComboBox->SetSelectedIndex(0); // �⺻������ ����
	if (MicModeComboBox) MicModeComboBox->SetSelectedIndex(0); // �⺻������ ����
}

void UPJEAudioSetting::OnBackButtonClicked()
{
	// ���� �޴��� ���ư���
	this->RemoveFromParent();
}
