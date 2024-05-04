// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_KeepMoving.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_KeepMoving : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_KeepMoving();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
