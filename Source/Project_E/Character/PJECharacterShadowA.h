// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadow.h"
#include "PJECharacterShadowA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowA : public APJECharacterShadow
{
	GENERATED_BODY()
public:
	APJECharacterShadowA();

protected:
	virtual void BeginPlay() override;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;


};
