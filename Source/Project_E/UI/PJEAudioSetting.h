#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PJEAudioSetting.generated.h"

UCLASS()
class PROJECT_E_API UPJEAudioSetting : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class USlider* MasterVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* BGMVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* EnvironmentVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* SFXVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* NarrationVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* VoiceChatVolumeSlider;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* SpeakerComboBox;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* MicModeComboBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* MasterSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* BGMSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* EnvironmentSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* SFXSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* NarrationSoundClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundClass* VoiceChatSoundClass;

private:
	UFUNCTION()
	void OnMasterVolumeChanged(float Value);

	UFUNCTION()
	void OnBGMVolumeChanged(float Value);

	UFUNCTION()
	void OnEnvironmentVolumeChanged(float Value);

	UFUNCTION()
	void OnSFXVolumeChanged(float Value);

	UFUNCTION()
	void OnNarrationVolumeChanged(float Value);

	UFUNCTION()
	void OnVoiceChatVolumeChanged(float Value);

	UFUNCTION()
	void OnSpeakerSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnMicModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnResetButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();


	void SetVolume(USoundClass* SoundClass, float Value);

	void SaveSettings();
	void LoadSettings();
	void ApplyDefaultSettings();
};
