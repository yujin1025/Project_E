// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowB.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"

APJECharacterShadowB::APJECharacterShadowB()
{
	MonsterRank = EMonsterRank::Elite;
	MaxHp = 100;
	MoveSpeed = 1.5f;
	PlayerDetectionRange = 1.0f;
	AttackSize = 1.6f;
	ChaseSpeed = 4.0f;
}

void APJECharacterShadowB::BeginPlay()
{
	Super::BeginPlay();

	ShadowGeneratorsCount = UPJEShadowGeneratorManager::GetInstance()->GetShadowGeneratorsCount();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);

	PlayerDetectionRange = 4.0f;
}

float APJECharacterShadowB::GetAIPatrolRadius()
{
	return 0.0f;
}

float APJECharacterShadowB::GetAIDetectRange()
{
	return 0.0f;
}

float APJECharacterShadowB::GetAIAttackRange()
{
	return 0.0f;
}

float APJECharacterShadowB::GetAITurnSpeed()
{
	return 0.0f;
}

float APJECharacterShadowB::GetChaseSpeed()
{
	return ChaseSpeed;
}

void APJECharacterShadowB::AttackByAI()
{
	//TODO :Implement this function
}
