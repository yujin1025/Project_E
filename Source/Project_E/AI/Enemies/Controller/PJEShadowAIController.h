// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PJEAIController.h"
#include "PJEShadowAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEShadowAIController : public APJEAIController
{
	GENERATED_BODY()

public:
    APJEShadowAIController();

protected:
	virtual void InitBB() override;
};
