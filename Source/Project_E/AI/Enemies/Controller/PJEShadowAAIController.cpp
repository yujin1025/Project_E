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
}

