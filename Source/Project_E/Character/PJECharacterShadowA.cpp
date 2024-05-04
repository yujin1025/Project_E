// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowA.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

APJECharacterShadowA::APJECharacterShadowA()
{
	ShadowGeneratorsCount = 0;

	MonsterRank = EMonsterRank::Normal;
	MaxHp = 50;
	SetCurrentHP(MaxHp);
	MoveSpeed = 2.0f;
	PlayerDetectionRange = 1.0f;
	KeepMovingDuration = 10.0f;
	BlinkDuration = 0.2f;
	TeleportRange = 2.0f;
}

float APJECharacterShadowA::GetKeepMovingDuration()
{
	return KeepMovingDuration;
}

void APJECharacterShadowA::BeginPlay()
{
	Super::BeginPlay();
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
