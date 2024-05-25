// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "CrossHairWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UCrossHairWidget : public UBaseWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	FVector2D GetScreenMousePosition();
	FVector2D GetAimScreenPosition(UImage* AimImage);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> AimPoint;
};
