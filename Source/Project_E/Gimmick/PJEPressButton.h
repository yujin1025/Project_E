// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJEPressButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEPressButton : public APJEButtonBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
};
