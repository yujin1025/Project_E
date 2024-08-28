// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PJEHpBarWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEHpBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UPJEHpBarWidgetComponent();

public:
	TSubclassOf<class UUserWidget> GetHpBarWidgetClass();

protected:
	UPROPERTY()
	TSubclassOf<class UUserWidget> HpBarWidgetClass;

	virtual void InitWidget() override;
};
