// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterBase.h"
#include "Interface/PJECharacterAIInterface.h"
#include "PJECharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterNonPlayer : public APJECharacterBase, public IPJECharacterAIInterface
{
	GENERATED_BODY()
public:
	APJECharacterNonPlayer();

protected:
	virtual void PostInitializeComponents() override;
protected:
	virtual void BeginPlay() override;
protected:
	void SetDead() override;
// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;

	//virtual void NotifyComboActionEnd() override;
};
