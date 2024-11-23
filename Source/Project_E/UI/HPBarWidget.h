// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "HPBarWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UHPBarWidget : public UBaseWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UTextBlock* HPText;

public:
	virtual void NativeConstruct() override;
};
