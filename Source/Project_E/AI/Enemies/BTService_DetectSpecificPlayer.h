// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectSpecificPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTService_DetectSpecificPlayer : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DetectSpecificPlayer();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
