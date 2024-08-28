// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PJEWorldSpaceWidget.h"
#include "PJEHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEHealthBarWidget : public UPJEWorldSpaceWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;
};
