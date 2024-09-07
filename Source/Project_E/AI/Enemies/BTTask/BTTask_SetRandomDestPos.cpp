#include "AI/Enemies/BTTask/BTTask_SetRandomDestPos.h"
#include "AI/PJEAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/Enemies/Controller/PJEShadowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationPath.h"

UBTTask_SetRandomDestPos::UBTTask_SetRandomDestPos()
{
}

EBTNodeResult::Type UBTTask_SetRandomDestPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
    
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (ControllingPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    Blackboard->SetValueAsVector(BBKEY_DESTPOS, ControllingPawn->GetActorLocation());

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (NavSystem == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error0"));
        return EBTNodeResult::Failed;
    }

    FVector SubPatrolPos;
    FNavLocation SubNavLocation;
    if (!(NavSystem->GetRandomReachablePointInRadius(Blackboard->GetValueAsVector(BBKEY_DESTPOS), 2000.0f, SubNavLocation)))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error1"));
    }
    SubPatrolPos = SubNavLocation.Location;
    Blackboard->SetValueAsVector(BBKEY_SUBDESTPOS, SubPatrolPos);
    
    FVector NextPatrolPos;
    FNavLocation NavLocation;
    if (!(NavSystem->GetRandomReachablePointInRadius(Blackboard->GetValueAsVector(BBKEY_SUBDESTPOS), 1000.0f, NavLocation)))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Error2"));
    }
    NextPatrolPos = NavLocation.Location;
    Blackboard->SetValueAsVector(BBKEY_DESTPOS, NextPatrolPos);

    return EBTNodeResult::Succeeded;
}
