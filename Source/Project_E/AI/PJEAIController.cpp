// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PJEAI.h"

void APJEAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		InitBB();
		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void APJEAIController::StopAI()
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

