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
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual uint16 GetInstanceMemorySize() const override;

private:
	void SpawnField(AActor* OwnerActor, uint8* NodeMemory);
	void DealDamage(AActor* DamagedActor, uint8* NodeMemory);
	void DestroyField(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category = "Field")
	float Radius = 160.0f; // 1.6m

	UPROPERTY(EditAnywhere, Category = "Field")
	float Duration = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamagePerSecond = 10.0f;
};

struct FBTSpawnFieldTaskMemory
{
	FTimerHandle TimerHandle_DestroyField;
	FTimerHandle TimerHandle_DealDamage;
	TArray<AActor*> OverlappingActors;
	UStaticMeshComponent* FieldMesh;
	float TimeElapsed;
};