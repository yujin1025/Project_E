// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "PopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPopUpWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
	//UPROPERTY(meta = (BindWidget))
	//class UProgressBar* HealthBar;
	
protected:
	virtual void NativeConstruct() override;

};
