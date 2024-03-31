// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PJEDropedItem.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEDropedItem : public AItemBase
{
	GENERATED_BODY()

public:
	APJEDropedItem();

protected:
	virtual void BeginPlay() override;
	
	virtual void BeginInteracting(const AActor* InteractActor) override;
	virtual void EndInteracting(const AActor* InteractActor) override;

	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;
	virtual void ShowInteractPointWidget() override;
	virtual void HideInteracPointWidget() override;

protected:
	UPROPERTY(EditInstanceOnly)
	int32 ItemCode;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* Widget;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* PointWidget;
};