// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowB.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAIController.h"
#include "AI/PJEAI.h"
#include "AI/Enemies/PJEShadowField.h"

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

	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);

	PlayerDetectionRange = 4.0f;

	OnDestroyed.AddDynamic(this, &APJECharacterShadowB::DestoryField);
}

float APJECharacterShadowB::GetChaseSpeed()
{
	return ChaseSpeed;
}

float APJECharacterShadowB::GetPlayerDetectRange()
{
	return PlayerDetectionRange * 100.0f;
}

float APJECharacterShadowB::GetDetectMaxYDifference()
{
	return MaxYDifference;
}

float APJECharacterShadowB::GetDetectMinYDifference()
{
	return MinYDifference;
}

float APJECharacterShadowB::GetFieldRadius()
{
	return FieldRadius;
}

float APJECharacterShadowB::GetFieldDuration()
{
	return FieldDuration;
}

float APJECharacterShadowB::GetDamagePerSecond()
{
	return DamagePerSecond;
}

void APJECharacterShadowB::SetFieldActor(APJEShadowField* NewFieldActor)
{
	FieldActor = NewFieldActor;
}

APJEShadowField* APJECharacterShadowB::GetFieldActor()
{
	return FieldActor;
}

float APJECharacterShadowB::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsBool(BBKEY_ISPLAYERNEARBY, true);
			BlackboardComp->SetValueAsObject(BBKEY_PLAYERACTOR, DamageCauser);
		}
	}
	return 0.0f;
}

void APJECharacterShadowB::DestoryField(AActor* DestroyedActor)
{
	if (FieldActor)
	{
		FieldActor->Destroy();
		FieldActor = nullptr;
	}
}
