// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadow.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <AI/PJEAI.h>

APJECharacterShadow::APJECharacterShadow()
{
	ShadowSpawnRadius = 1000.0f;
	bReplicates = true;
}

void APJECharacterShadow::BeginPlay()
{
	Super::BeginPlay();
	SetReplicateMovement(true);
	MoveSpeed *= 100.0f;
	RallyPoint = FVector(0, 0, 0);
}

void APJECharacterShadow::SetShadowGeneratorsCount(int32 NewShadowGeneratorsCount)
{
	ShadowGeneratorsCount = NewShadowGeneratorsCount;
}

float APJECharacterShadow::GetShadowSpawnRadius() const
{
	return ShadowSpawnRadius;
}

void APJECharacterShadow::SetRallyPoint(FVector NewPoint)
{
	RallyPoint = NewPoint;
}

FVector APJECharacterShadow::GetRallyPoint()
{
	return RallyPoint;
}

void APJECharacterShadow::InitBB()
{
    AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
        if (BlackboardComp)
        {
            BlackboardComp->SetValueAsVector(BBKEY_DESTPOS, GetRallyPoint());
            if (GetRallyPoint() != FVector(0, 0, 0))
            {
                BlackboardComp->SetValueAsBool(BBKEY_SHOULDMOVETOPOINT, true);
            }
            else
            {
                BlackboardComp->SetValueAsBool(BBKEY_SHOULDMOVETOPOINT, false);
            }
        }
    }
}
