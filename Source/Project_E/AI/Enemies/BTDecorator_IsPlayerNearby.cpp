// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTDecorator_IsPlayerNearby.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsPlayerNearby::UBTDecorator_IsPlayerNearby()
{
	NodeName = TEXT("IsPlayerNearby");
}

bool UBTDecorator_IsPlayerNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        bool bIsPlayerNearby = BlackboardComp->GetValueAsBool(TEXT("bIsPlayerNearby"));
        return bIsPlayerNearby;
    }

	return false;
}
