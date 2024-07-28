// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

APJECharacterShadowC::APJECharacterShadowC()
{
	MonsterRank = EMonsterRank::Boss;
	MaxHp = 200;
	MoveSpeed = 4.7f;
	PlayerDetectionRange = 1.0f;
}

float APJECharacterShadowC::GetBlinkDuration()
{
	return BlinkDuration;
}

float APJECharacterShadowC::GetSingleBlinkDuration()
{
	return SingleBlinkDuration;
}

float APJECharacterShadowC::GetTeleportRange()
{
	return TeleportRange * 100.0f;
}

void APJECharacterShadowC::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);

	PlayerDetectionRange = 4.0f;
}

float APJECharacterShadowC::GetAIPatrolRadius()
{
	return 0.0f;
}

float APJECharacterShadowC::GetAIDetectRange()
{
	return 0.0f;
}

float APJECharacterShadowC::GetAIAttackRange()
{
	return 0.0f;
}

float APJECharacterShadowC::GetAITurnSpeed()
{
	return 0.0f;
}

void APJECharacterShadowC::AttackByAI()
{
	//TODO :Implement this function
}
