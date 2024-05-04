// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Teleport.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Teleport::UBTTask_Teleport()
{
    NodeName = "Random Teleport";
}

EBTNodeResult::Type UBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Pawn = AICon->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    FVector CurrentLocation = Pawn->GetActorLocation();
    FNavLocation RandomNavLocation;
    float Radius = 800.0f;

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSys || !NavSys->GetRandomPointInNavigableRadius(CurrentLocation, Radius, RandomNavLocation))
    {
        return EBTNodeResult::Failed;
    }

    Pawn->SetActorLocation(RandomNavLocation.Location);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool("bIsPlayerNearby", false);
    return EBTNodeResult::Succeeded;
}
