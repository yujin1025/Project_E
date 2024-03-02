// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterNonPlayer.h"
#include "PJECharacterBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterBoss : public APJECharacterNonPlayer
{
	GENERATED_BODY()
public:
	APJECharacterBoss();

protected:
	virtual void BeginPlay() override;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void AttackByAI() override;
// TODO : Special Attack, etc...
};
