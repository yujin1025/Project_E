// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_SetRandomDestPos.h"
#include "AI/PJEAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetRandomDestPos::UBTTask_SetRandomDestPos()
{
}

EBTNodeResult::Type UBTTask_SetRandomDestPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if (nullptr == NavSystem)
	{
		return EBTNodeResult::Failed;
	}

	FVector OriPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_ORIPOS);
	FNavLocation NextPatrolPos;
	FNavLocation SubPatrolPos;

	if (NavSystem->GetRandomPointInNavigableRadius(OriPos, 2000.0f, NextPatrolPos))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_DESTPOS, NextPatrolPos.Location);
	}
	if (NavSystem->GetRandomPointInNavigableRadius(OriPos, 1000.0f, SubPatrolPos))
	{

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_SUBDESTPOS, SubPatrolPos.Location);
	}

	return EBTNodeResult::Succeeded;
}
