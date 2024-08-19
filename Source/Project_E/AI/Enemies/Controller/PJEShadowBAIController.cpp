// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEShadowBAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PJECharacterShadowB.h"
#include "AI/PJEAI.h"

APJEShadowBAIController::APJEShadowBAIController()
{
}

void APJEShadowBAIController::InitBB()
{
	Super::InitBB();
	APJECharacterShadowB* OwnCharacter = Cast<APJECharacterShadowB>(GetPawn());
	Blackboard->SetValueAsFloat(TEXT("PlayerDetectRange"), OwnCharacter->GetPlayerDetectRange());
}
