#pragma once

#include "CoreMinimal.h"
#include "UI/PopUpWidget.h"
#include "PJESystemWidget.generated.h"

UCLASS()
class PROJECT_E_API UPJESystemWidget : public UPopUpWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ResolutionComboBox;

	UPROPERTY(meta = (BindWidget))
	class UComboBoxString* ScreenModeComboBox;

	UPROPERTY(meta = (BindWidget))
	class USlider* CameraSpeedSlider;

	UPROPERTY(meta = (BindWidget))
	class USlider* BrightnessSlider;

	UPROPERTY(meta = (BindWidget))
	class UButton* ResetButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

	UFUNCTION()
	void OnResolutionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnScreenModeChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnCameraSpeedChanged(float Value);

	UFUNCTION()
	void OnBrightnessChanged(float Value);

	UFUNCTION()
	void OnResetButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

private:
	UPROPERTY()
	TObjectPtr<class APostProcessVolume> PostProcessVolume;

	UPROPERTY()
	TObjectPtr<class UPJEGameInstance> GameInstance;

// SaveSection
private:
	void SaveSettings();
	void LoadSettings();
	void ApplyDefaultSettings();


};
