// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FirstAttackDone.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_FirstAttackDone : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FirstAttackDone();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
