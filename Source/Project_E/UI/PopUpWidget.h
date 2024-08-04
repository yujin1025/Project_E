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
	UPopUpWidget();

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

};
