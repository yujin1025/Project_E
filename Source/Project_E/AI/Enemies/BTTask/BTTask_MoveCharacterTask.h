// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveCharacterTask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_MoveCharacterTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	bool IsLocationInNavMesh(ACharacter* CurrentCharacter, FVector TargetLocation);
	bool IsFrontEmpty(ACharacter* CurrentCharacter, FVector DirVec);
	bool IsCliff(ACharacter* CurrentCharacter, FVector DirVec);
	
};
