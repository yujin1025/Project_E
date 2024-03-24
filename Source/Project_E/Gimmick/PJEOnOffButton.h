// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJEOnOffButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEOnOffButton : public APJEButtonBase
{
	GENERATED_BODY()

public:
	APJEOnOffButton();

	/** Interaction */
	virtual void BeginInteracting() override;
	virtual void EndInteracting() override;
	/** end Interaction */

public:
	virtual void Tick(float DeltaTime) override;
	
};
