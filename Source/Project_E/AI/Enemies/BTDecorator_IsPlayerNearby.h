// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsPlayerNearby.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTDecorator_IsPlayerNearby : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsPlayerNearby();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector IsPlayerNearbyKey;
};
