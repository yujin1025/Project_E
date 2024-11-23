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

protected:
	UPROPERTY()
	TObjectPtr<class UHealthComponent> HealthComponent;

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealthBar();

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;

	void SetHealthComponent(class UHealthComponent* NewHealthComponent);
};
