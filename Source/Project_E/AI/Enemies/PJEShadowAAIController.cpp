// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/PJEAI.h"

APJEShadowAAIController::APJEShadowAAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrints/AI/Enemies/BB_PJE_ShadowA.BB_PJE_ShadowA'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/BluePrints/AI/Enemies/BT_PJE_ShadowA.BT_PJE_ShadowA'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
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


