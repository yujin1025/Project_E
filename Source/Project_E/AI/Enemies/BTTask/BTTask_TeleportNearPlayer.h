// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TeleportNearPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_TeleportNearPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_TeleportNearPlayer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
