// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_FirstAttackDone.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FirstAttackDone::UBTTask_FirstAttackDone()
{
}

EBTNodeResult::Type UBTTask_FirstAttackDone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	BlackboardComp->SetValueAsBool(TEXT("bIsFirstAttackDone"), true);

	return EBTNodeResult::Succeeded;
}
