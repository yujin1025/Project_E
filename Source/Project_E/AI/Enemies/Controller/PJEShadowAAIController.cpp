// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/Controller/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/PJEAI.h"
#include <Net/UnrealNetwork.h>

APJEShadowAAIController::APJEShadowAAIController()
{
    
}

void APJEShadowAAIController::InitBB()
{
	Super::InitBB();
	APJECharacterShadowA* OwnCharacter = Cast<APJECharacterShadowA>(GetPawn());
	//Blackboard->SetValueAsFloat(TEXT("MaxKeepMovingTime"), OwnCharacter->GetMaxKeepMovingTime());
	//Blackboard->SetValueAsFloat(TEXT("BlinkDuration"), OwnCharacter->GetBlinkDuration());
	//Blackboard->SetValueAsFloat(TEXT("SingleBlinkDuration"), OwnCharacter->GetSingleBlinkDuration());
	//Blackboard->SetValueAsFloat(TEXT("TeleportRange"), OwnCharacter->GetTeleportRange());
	//Blackboard->SetValueAsFloat(TEXT("PlayerDetectRange"), OwnCharacter->GetPlayerDetectRange());
	Blackboard->SetValueAsVector(BBKEY_ORIPOS, OwnCharacter->GetActorLocation());
}

