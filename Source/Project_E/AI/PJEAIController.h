// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PJEAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEAIController : public AAIController
{
	GENERATED_BODY()
public:
	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void InitBB();

public:
	TObjectPtr<class UBlackboardData> GetBB();
	
	TObjectPtr<class UBehaviorTree> GetBT();

protected:
	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};
