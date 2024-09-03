// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PJEAI.h"
#include "Net/UnrealNetwork.h"

APJEAIController::APJEAIController()
{
}

void APJEAIController::RunAI()
{
    if (HasAuthority())
    {
        Server_RunAI();
    }
}

void APJEAIController::StopAI()
{
    if (HasAuthority())
    {
        Server_StopAI();
    }
}

void APJEAIController::Server_RunAI_Implementation()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        InitBB();
        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }
}

bool APJEAIController::Server_RunAI_Validate()
{
    return true;
}

void APJEAIController::Server_StopAI_Implementation()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent)
    {
        BTComponent->StopTree();
    }
}

bool APJEAIController::Server_StopAI_Validate()
{
    return true;
}

void APJEAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    RunAI();
}

void APJEAIController::InitBB()
{
    Blackboard->SetValueAsVector(BBKEY_SUBDESTPOS, FVector(0, 0, 0));
    Blackboard->SetValueAsVector(BBKEY_DESTPOS, GetPawn()->GetActorLocation());
}

UBlackboardData* APJEAIController::GetBB()
{
    return BBAsset;
}

UBehaviorTree* APJEAIController::GetBT()
{
    return BTAsset;
}
