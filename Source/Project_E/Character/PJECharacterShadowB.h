// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadowA.h"
#include "PJECharacterShadowB.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowB : public APJECharacterShadow
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

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;
	virtual void AttackByAI() override;
};
