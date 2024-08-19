// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_ChasePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "AI/PJEAI.h"

UBTTask_ChasePlayer::UBTTask_ChasePlayer()
{
    NodeName = "Chase Player";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    return EBTNodeResult::InProgress;
}

void UBTTask_ChasePlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    AAIController* AICon = OwnerComp.GetAIOwner();
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

    if (!AICon || !BlackboardComp)
    {
        return;
    }

    AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_PLAYERACTOR));
    if (!TargetActor)
    {
        return;
    }

    AICon->MoveToLocation(TargetActor->GetActorLocation(), 0.0001f, true, false, false, false, nullptr, true);
}
