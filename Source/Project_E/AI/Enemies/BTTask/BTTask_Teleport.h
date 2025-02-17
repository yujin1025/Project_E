// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_Teleport : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Teleport();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
