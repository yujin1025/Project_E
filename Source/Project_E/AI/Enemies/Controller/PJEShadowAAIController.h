// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PJEAIController.h"
#include "PJEShadowAAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEShadowAAIController : public APJEAIController
{
	GENERATED_BODY()
public:
	APJEShadowAAIController();

protected:
	virtual void InitBB() override;


};
