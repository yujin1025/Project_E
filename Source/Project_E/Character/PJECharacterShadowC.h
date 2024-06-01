// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterNonPlayer.h"
#include "Character/PJECharacterShadow.h"
#include "PJECharacterShadowC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowC : public APJECharacterShadow
{
	GENERATED_BODY()
	
public:
	APJECharacterShadowC();
	
	void BeginPlay();

	float GetAIPatrolRadius();

	float GetAIDetectRange();

	float GetAIAttackRange();

	float GetAITurnSpeed();

	void AttackByAI();

};
