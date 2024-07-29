#include "UI/PJEAudioSetting.h"
#include "Components/Slider.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "Sound/SoundClass.h"
#include "Kismet/GameplayStatics.h"
#include "Project_E/PJEAudioSettingsSaveGame.h"

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
        SpeakerComboBox->AddOption(TEXT("Default"));
        SpeakerComboBox->AddOption(TEXT("Speaker"));
        SpeakerComboBox->AddOption(TEXT("Headphones"));
    }

    if (MicModeComboBox)
    {
        MicModeComboBox->OnSelectionChanged.AddDynamic(this, &UPJEAudioSetting::OnMicModeSelectionChanged);
        MicModeComboBox->AddOption(TEXT("Voice Detection"));
        MicModeComboBox->AddOption(TEXT("Push to Talk"));
    }

    if (ResetButton)
    {
        ResetButton->OnClicked.AddDynamic(this, &UPJEAudioSetting::OnResetButtonClicked);
    }

    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UPJEAudioSetting::OnBackButtonClicked);
    }

    // Load settings or apply default settings if first run
    if (UGameplayStatics::DoesSaveGameExist(TEXT("AudioSettings"), 0))
    {
        LoadSettings();
    }
    else
    {
        ApplyDefaultSettings();
        SaveSettings();
    }
}

void UPJEAudioSetting::OnMasterVolumeChanged(float Value)
{
    SetVolume(MasterSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnBGMVolumeChanged(float Value)
{
    SetVolume(BGMSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnEnvironmentVolumeChanged(float Value)
{
    SetVolume(EnvironmentSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnSFXVolumeChanged(float Value)
{
    SetVolume(SFXSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnNarrationVolumeChanged(float Value)
{
    SetVolume(NarrationSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnVoiceChatVolumeChanged(float Value)
{
    SetVolume(VoiceChatSoundClass, Value);
    SaveSettings();
}

void UPJEAudioSetting::OnSpeakerSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    // Speaker selection logic
    SaveSettings();
}

void UPJEAudioSetting::OnMicModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
    // Mic mode selection logic
    SaveSettings();
}

void UPJEAudioSetting::OnResetButtonClicked()
{
    ApplyDefaultSettings();
    SaveSettings();
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

void UPJEAudioSetting::SaveSettings()
{
    const FString SaveSlotName = TEXT("AudioSettings");
    const int32 UserIndex = 0;

    UAudioSettingsSaveGame* SaveGameInstance = Cast<UAudioSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UAudioSettingsSaveGame::StaticClass()));

    if (SaveGameInstance)
    {
        SaveGameInstance->MasterVolume = MasterVolumeSlider->GetValue();
        SaveGameInstance->BGMVolume = BGMVolumeSlider->GetValue();
        SaveGameInstance->EnvironmentVolume = EnvironmentVolumeSlider->GetValue();
        SaveGameInstance->SFXVolume = SFXVolumeSlider->GetValue();
        SaveGameInstance->NarrationVolume = NarrationVolumeSlider->GetValue();
        SaveGameInstance->VoiceChatVolume = VoiceChatVolumeSlider->GetValue();
        SaveGameInstance->SpeakerMode = SpeakerComboBox->GetSelectedOption();
        SaveGameInstance->MicMode = MicModeComboBox->GetSelectedOption();

        if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex))
        {
            UE_LOG(LogTemp, Log, TEXT("Settings saved successfully."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to save settings."));
        }
    }
}

void UPJEAudioSetting::LoadSettings()
{
    const FString SaveSlotName = TEXT("AudioSettings");
    const int32 UserIndex = 0;

    UAudioSettingsSaveGame* LoadGameInstance = Cast<UAudioSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

    if (LoadGameInstance)
    {
        if (MasterVolumeSlider)
        {
            MasterVolumeSlider->SetValue(LoadGameInstance->MasterVolume);
            UE_LOG(LogTemp, Log, TEXT("MasterVolume loaded: %f"), LoadGameInstance->MasterVolume);
        }
        if (BGMVolumeSlider)
        {
            BGMVolumeSlider->SetValue(LoadGameInstance->BGMVolume);
            UE_LOG(LogTemp, Log, TEXT("BGMVolume loaded: %f"), LoadGameInstance->BGMVolume);
        }
        if (EnvironmentVolumeSlider)
        {
            EnvironmentVolumeSlider->SetValue(LoadGameInstance->EnvironmentVolume);
            UE_LOG(LogTemp, Log, TEXT("EnvironmentVolume loaded: %f"), LoadGameInstance->EnvironmentVolume);
        }
        if (SFXVolumeSlider)
        {
            SFXVolumeSlider->SetValue(LoadGameInstance->SFXVolume);
            UE_LOG(LogTemp, Log, TEXT("SFXVolume loaded: %f"), LoadGameInstance->SFXVolume);
        }
        if (NarrationVolumeSlider)
        {
            NarrationVolumeSlider->SetValue(LoadGameInstance->NarrationVolume);
            UE_LOG(LogTemp, Log, TEXT("NarrationVolume loaded: %f"), LoadGameInstance->NarrationVolume);
        }
        if (VoiceChatVolumeSlider)
        {
            VoiceChatVolumeSlider->SetValue(LoadGameInstance->VoiceChatVolume);
            UE_LOG(LogTemp, Log, TEXT("VoiceChatVolume loaded: %f"), LoadGameInstance->VoiceChatVolume);
        }
        if (SpeakerComboBox)
        {
            SpeakerComboBox->SetSelectedOption(LoadGameInstance->SpeakerMode);
            UE_LOG(LogTemp, Log, TEXT("SpeakerMode loaded: %s"), *LoadGameInstance->SpeakerMode);
        }
        if (MicModeComboBox)
        {
            MicModeComboBox->SetSelectedOption(LoadGameInstance->MicMode);
            UE_LOG(LogTemp, Log, TEXT("MicMode loaded: %s"), *LoadGameInstance->MicMode);
        }

        UE_LOG(LogTemp, Log, TEXT("Settings loaded successfully."));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load settings."));
    }
}

void UPJEAudioSetting::ApplyDefaultSettings()
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
