// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowA.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

APJECharacterShadowA::APJECharacterShadowA()
{
	ShadowGeneratorsCount = 0;

	MonsterRank = EMonsterRank::Normal;
	MaxHp = 50;
	MoveSpeed = 2.0f;
	PlayerDetectionRange = 4.0f;
	MaxKeepMovingTime = 4.0f;
	BlinkDuration = 0.6f;
	TeleportRange = 2.0f;
	SingleBlinkDuration = 0.2f;
}

float APJECharacterShadowA::GetMaxKeepMovingTime()
{
	return MaxKeepMovingTime;
}

float APJECharacterShadowA::GetBlinkDuration()
{
	return BlinkDuration;
}

float APJECharacterShadowA::GetSingleBlinkDuration()
{
	return SingleBlinkDuration;
}

float APJECharacterShadowA::GetTeleportRange()
{
	return TeleportRange * 100.0f;
}

void APJECharacterShadowA::BeginPlay()
{
	Super::BeginPlay();
	ShadowGeneratorsCount = UPJEShadowGeneratorManager::GetInstance()->GetShadowGeneratorsCount();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);
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
