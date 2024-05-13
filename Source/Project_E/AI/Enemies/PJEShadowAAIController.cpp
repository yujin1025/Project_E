// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/PJEAI.h"

APJEShadowAAIController::APJEShadowAAIController()
{
	;
}

void APJEShadowAAIController::InitBB()
{
	Super::InitBB();
	APJECharacterShadowA* OwnCharacter = Cast<APJECharacterShadowA>(GetPawn());
	Blackboard->SetValueAsFloat("MaxKeepMovingTime", OwnCharacter->GetMaxKeepMovingTime());
	Blackboard->SetValueAsFloat("BlinkDuration", OwnCharacter->GetBlinkDuration());
	Blackboard->SetValueAsFloat("SingleBlinkDuration", OwnCharacter->GetSingleBlinkDuration());
	Blackboard->SetValueAsFloat("TeleportRange", OwnCharacter->GetTeleportRange());
	Blackboard->SetValueAsFloat("PlayerDetectRange", OwnCharacter->GetPlayerDetectRange());
}


