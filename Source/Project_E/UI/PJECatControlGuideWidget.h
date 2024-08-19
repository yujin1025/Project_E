// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PopUpWidget.h"
#include "PJECatControlGuideWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJECatControlGuideWidget : public UPopUpWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnBackButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* BackButton;
};
