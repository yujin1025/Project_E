// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BackRush.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_BackRush : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
    UBTTask_BackRush();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    virtual uint16 GetInstanceMemorySize() const override;
};

USTRUCT()
struct FBTBackRushTaskMemory
{
    GENERATED_BODY()

    public:
    FVector TargetLocation;
};