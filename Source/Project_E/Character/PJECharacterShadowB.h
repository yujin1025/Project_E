// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/Enemies/Interface/PJEFieldSpawnable.h"
#include "AI/Enemies/Interface/PJEChasable.h"
#include "PJECharacterShadowB.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowB : public APJECharacterShadow, public IPJEFieldSpawnable, public IPJEChasable
{
	GENERATED_BODY()
public:
	APJECharacterShadowB();

protected:
	virtual void BeginPlay() override;

// Stat Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ChaseSpeed;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;
	virtual float GetChaseSpeed() override;
	virtual void AttackByAI() override;
};
