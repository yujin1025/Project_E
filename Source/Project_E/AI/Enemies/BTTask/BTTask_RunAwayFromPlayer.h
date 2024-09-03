// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/BTTask/BTTask_MoveCharacterTask.h"
#include "BTTask_RunAwayFromPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_RunAwayFromPlayer : public UBTTask_MoveCharacterTask
{
	GENERATED_BODY()
	
public:
	UBTTask_RunAwayFromPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetInstanceMemorySize() const override;
};


USTRUCT()
struct FRunAwayFromPlayerTaskMemory
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<class IPJERunAwayable> RunAwayable;
	float KeepMovingTime;
	float RandomDegree;
	float LastMaxMoveSpeed;
};