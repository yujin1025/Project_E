// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_Teleport.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"
#include "Project_E/AI/Enemies/Interface/PJETeleportable.h"

UBTTask_Teleport::UBTTask_Teleport()
{
    NodeName = "Random Teleport";
}

EBTNodeResult::Type UBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());
    FVector CurrentLocation = OwnerActor->GetActorLocation();
    FNavLocation RandomNavLocation;

    IPJETeleportable* Teleportable = Cast<IPJETeleportable>(OwnerActor);
    float Radius = Teleportable->GetTeleportRange();

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

    OwnerActor->SetActorLocation(RandomNavLocation.Location);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_PLAYERACTOR, nullptr);
    return EBTNodeResult::Succeeded;
}

