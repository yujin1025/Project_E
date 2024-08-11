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
	void UpdateOverlappingActors(const FVector& Location, uint8* NodeMemory);
	virtual uint16 GetInstanceMemorySize() const override;

private:
	void SpawnField(AActor* OwnerActor, uint8* NodeMemory);
	void DealDamage(AActor* DamagedActor, uint8* NodeMemory);
	void DestroyField(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	/*
	UPROPERTY(EditAnywhere, Category = "Field")
	float Radius = 160.0f; // 1.6m

	UPROPERTY(EditAnywhere, Category = "Field")
	float Duration = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float DamagePerSecond = 0.1f;
	*/
};

struct FBTSpawnFieldTaskMemory
{
	FTimerHandle TimerHandle_DestroyField;
	FTimerHandle TimerHandle_DealDamage;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappingActors;

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> FieldMesh;

	UPROPERTY()
	TObjectPtr<class IPJEFieldSpawnable> FieldSpawnable;

	float TimeElapsed;
	float DamageElapsedTime;
};