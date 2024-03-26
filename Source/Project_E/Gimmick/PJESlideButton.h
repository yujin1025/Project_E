// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJESlideButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJESlideButton : public APJEButtonBase
{
	GENERATED_BODY()

public:
	APJESlideButton();

	/** Interaction */
	virtual void BeginInteracting(const AActor* InteractActor) override;
	virtual void EndInteracting(const AActor* InteractActor) override;
	/** end Interaction */

	
};
