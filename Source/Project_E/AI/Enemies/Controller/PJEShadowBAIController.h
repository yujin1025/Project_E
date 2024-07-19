// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/Controller/PJEShadowAIController.h"
#include "PJEShadowBAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEShadowBAIController : public APJEShadowAIController
{
	GENERATED_BODY()
	
public:
	APJEShadowBAIController();

protected:
	virtual void InitBB() override;
	
};
