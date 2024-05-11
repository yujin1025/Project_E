// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Teleport.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"

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
    float Radius = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_TELEPORTRANGE);

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    const int32 MaxAttempts = 10;  // 시도 횟수 제한
    int32 Attempts = 0;
    bool bLocationFound = false;

    while (Attempts < MaxAttempts)
    {
        if (NavSys->GetRandomPointInNavigableRadius(CurrentLocation, Radius, RandomNavLocation))
        {
            bLocationFound = true;
            break;
        }

        Attempts++;
    }

    if (!bLocationFound)
    {
        return EBTNodeResult::Failed;
    }

    Pawn->SetActorLocation(RandomNavLocation.Location);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    return EBTNodeResult::Succeeded;
}

