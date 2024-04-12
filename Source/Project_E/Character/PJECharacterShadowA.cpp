// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowA.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"

APJECharacterShadowA::APJECharacterShadowA()
{
	ShadowGeneratorsCount = 0;
}

void APJECharacterShadowA::BeginPlay()
{
	Super::BeginPlay();
	//
	ShadowGeneratorsCount = UPJEShadowGeneratorManager::GetInstance()->GetShadowGeneratorsCount();
}

float APJECharacterShadowA::GetAIPatrolRadius()
{
	return 0.0f;
}

float APJECharacterShadowA::GetAIDetectRange()
{
	return 0.0f;
}

float APJECharacterShadowA::GetAIAttackRange()
{
	return 0.0f;
}

float APJECharacterShadowA::GetAITurnSpeed()
{
	return 0.0f;
}

void APJECharacterShadowA::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
}

void APJECharacterShadowA::AttackByAI()
{
	return;
}
