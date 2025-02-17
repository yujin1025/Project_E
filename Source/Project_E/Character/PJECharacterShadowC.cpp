// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowC.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAIController.h"
#include "AI/PJEAI.h"
#include "AI/Enemies/PJEShadowField.h"

APJECharacterShadowC::APJECharacterShadowC()
{
	MonsterRank = EMonsterRank::Boss;
	MaxHp = 200;
	MoveSpeed = 4.7f;
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

float APJECharacterShadowC::GetFieldRadius()
{
	return FieldRadius;
}

float APJECharacterShadowC::GetFieldDuration()
{
	return FieldDuration;
}

float APJECharacterShadowC::GetDamagePerSecond()
{
	return DamagePerSecond;
}

void APJECharacterShadowC::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);

	OnDestroyed.AddDynamic(this, &APJECharacterShadowC::DestoryField);
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

float APJECharacterShadowC::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool(BBKEY_ISFIRSTATTACKED, true);
		}
	}
	return 0.0f;
}

void APJECharacterShadowC::SetFieldActor(APJEShadowField* NewFieldActor)
{
	FieldActor = NewFieldActor;
}

APJEShadowField* APJECharacterShadowC::GetFieldActor()
{
	return FieldActor;
}

void APJECharacterShadowC::DestoryField(AActor* DestroyedActor)
{
	if (FieldActor)
	{
		FieldActor->Destroy();
		FieldActor = nullptr;
	}
}
