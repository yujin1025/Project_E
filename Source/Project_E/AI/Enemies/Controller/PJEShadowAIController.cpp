// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/Controller/PJEShadowAIController.h"
#include <AI/PJEAI.h>
#include <Net/UnrealNetwork.h>
#include <NavigationSystem.h>
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

APJEShadowAIController::APJEShadowAIController()
{
    bReplicates = true;
    SubPatrolPos = FVector(0, 0, 0);
}

void APJEShadowAIController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APJEShadowAIController, NextPatrolPos);
    DOREPLIFETIME(APJEShadowAIController, SubPatrolPos);
}

void APJEShadowAIController::OnRep_NextPatrolPos()
{

    if (Blackboard)
    {
        Blackboard->SetValueAsVector(BBKEY_DESTPOS, NextPatrolPos);
    }
}

void APJEShadowAIController::OnRep_SubPatrolPos()
{

    if (Blackboard)
    {
        Blackboard->SetValueAsVector(BBKEY_SUBDESTPOS, SubPatrolPos);
    }
}


void APJEShadowAIController::Server_SetRandomDestPos_Implementation(const FVector& OriPos)
{
    APawn* ControllingPawn = GetPawn();
    if (nullptr == ControllingPawn)
    {
        return;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (nullptr == NavSystem)
    {
        return;
    }

    FNavLocation NextPatrolPosLoc;
    FNavLocation SubPatrolPosLoc;

    if (SubPatrolPos == FVector(0, 0, 0))
    {
        if (NavSystem->GetRandomPointInNavigableRadius(OriPos, 1000.0f, SubPatrolPosLoc))
        {
            SubPatrolPos = SubPatrolPosLoc.Location;
        }
    }
    else
    {
        SubPatrolPos = NextPatrolPos;
    }

    if (NavSystem->GetRandomPointInNavigableRadius(OriPos, 2000.0f, NextPatrolPosLoc))
    {
        NextPatrolPos = NextPatrolPosLoc.Location;
    }

    // 블랙보드에 값 설정
    if (Blackboard)
    {
        Blackboard->SetValueAsVector(BBKEY_DESTPOS, NextPatrolPos);
        Blackboard->SetValueAsVector(BBKEY_SUBDESTPOS, SubPatrolPos);
    }
}

bool APJEShadowAIController::Server_SetRandomDestPos_Validate(const FVector& OriPos)
{
    return true;
}
