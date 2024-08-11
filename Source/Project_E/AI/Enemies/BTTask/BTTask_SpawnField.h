// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SpawnField.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UBTTask_SpawnField : public UBTTaskNode
{
	GENERATED_BODY()

	public:
	UBTTask_SpawnField();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual uint16 GetInstanceMemorySize() const override;

private:
	void SpawnField(AActor* OwnerActor, uint8* NodeMemory);
};

struct FBTSpawnFieldTaskMemory
{
	UPROPERTY()
	TObjectPtr<class IPJEFieldSpawnable> FieldSpawnable;

	float TimeElapsed;
};