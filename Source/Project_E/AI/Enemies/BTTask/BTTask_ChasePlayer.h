// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Enemies/BTTask/BTTask_MoveCharacterTask.h"
#include "BTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_ChasePlayer : public UBTTask_MoveCharacterTask
{
	GENERATED_BODY()
	
protected:
	UBTTask_ChasePlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
