// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PJEAI.h"
#include "Net/UnrealNetwork.h"

APJEAIController::APJEAIController()
{
    bReplicates = true;
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
    Multicast_RunAI();
}

bool APJEAIController::Server_RunAI_Validate()
{
    return true;
}

void APJEAIController::Server_StopAI_Implementation()
{
    Multicast_StopAI();
}

bool APJEAIController::Server_StopAI_Validate()
{
    return true;
}

void APJEAIController::Multicast_RunAI_Implementation()
{
    UBlackboardComponent* BlackboardPtr = Blackboard.Get();
    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        InitBB();
        bool RunResult = RunBehaviorTree(BTAsset);
        ensure(RunResult);
    }
}

void APJEAIController::Multicast_StopAI_Implementation()
{
    UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (BTComponent)
    {
        BTComponent->StopTree();
    }
}

void APJEAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    RunAI();
}

void APJEAIController::InitBB()
{
    Blackboard->SetValueAsVector(BBKEY_ORIPOS, GetPawn()->GetActorLocation());
}

TObjectPtr<class UBlackboardData> APJEAIController::GetBB()
{
    return BBAsset;
}

TObjectPtr<class UBehaviorTree> APJEAIController::GetBT()
{
    return BTAsset;
}

void APJEAIController::OnRep_BBAsset()
{
    ;
}

void APJEAIController::OnRep_BTAsset()
{
    ;
}

void APJEAIController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APJEAIController, BBAsset);
    DOREPLIFETIME(APJEAIController, BTAsset);
}