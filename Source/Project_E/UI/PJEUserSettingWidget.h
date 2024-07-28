// PJEUserSettingWidget.h

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PJEUserSettingWidget.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_E_API UPJEUserSettingWidget : public UUserWidget
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
	TSubclassOf<class UUserWidget> SystemSettingsWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> AudioSettingWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> DuckGuideWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> CatGuideWidgetClass;

	UUserWidget* SystemSettingsWidget;

	UUserWidget* AudioSettingWidget;

	UUserWidget* DuckGuideWidget;
	UUserWidget* CatGuideWidget;
};
