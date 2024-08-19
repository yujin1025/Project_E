// PJEUserSettingWidget.h

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUpWidget.h"
#include "PJEUserSettingWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_E_API UPJEUserSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()

	public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SystemButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SoundButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* GuideButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenuButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;

private:
	UFUNCTION()
	void OnSystemButtonClicked();

	UFUNCTION()
	void OnSoundButtonClicked();

	UFUNCTION()
	void OnGuideButtonClicked();

	UFUNCTION()
	void OnMainMenuButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UPopUpWidget> SystemSettingsWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UPopUpWidget> AudioSettingWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UPopUpWidget> DuckGuideWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UPopUpWidget> CatGuideWidgetClass;

	UPROPERTY()
	TWeakObjectPtr<class UPopUpWidget> SystemSettingsWidget;
	UPROPERTY()
	TWeakObjectPtr<class UPopUpWidget> AudioSettingWidget;
	UPROPERTY()
	TWeakObjectPtr<class UPopUpWidget> DuckGuideWidget;
	UPROPERTY()
	TWeakObjectPtr<class UPopUpWidget> CatGuideWidget;
};
