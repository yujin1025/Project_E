// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SmoothMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_SmoothMoveTo : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SmoothMoveTo();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	FVector CalculateQuadraticBezierPoint(float t, FVector p0, FVector p1, FVector p2);
	void SmoothTransitionToNewTarget(UBehaviorTreeComponent& OwnerComp, FVector& CurrentTarget, FVector& NewTarget, float TransitionSpeed);
private:

};
