// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_SmoothMoveTo.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "NavigationSystem.h"

UBTTask_SmoothMoveTo::UBTTask_SmoothMoveTo()
{
	NodeName = "Smooth Move To";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SmoothMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    return EBTNodeResult::InProgress;
}

void UBTTask_SmoothMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        return;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    ACharacter* Character = AIController ? Cast<ACharacter>(AIController->GetPawn()) : nullptr;
    if (!Character)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (nullptr == NavSystem)
    {
        return;
    }

    FVector NewLocation = CalculateQuadraticBezierPoint(OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS), Character->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_SUBDESTPOS), OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_DESTPOS));
    FVector DirVec = NewLocation - Character->GetActorLocation();
    DirVec.Normalize();
    AIController->MoveToLocation(Character->GetActorLocation() + DirVec * 100.0f, -1.0f, false, false, false, false, nullptr, true);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_PROGRESS, OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS) + DeltaSeconds * 0.4);

    if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS) >= 0.9)
    {
        
        FVector CurrentDest = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_DESTPOS);
        FNavLocation NextPatrolPos;
        if (NavSystem->GetRandomPointInNavigableRadius(CurrentDest, 3000.0f, NextPatrolPos))
        {
            
            FVector NewDest = NextPatrolPos.Location;
            
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_SUBDESTPOS, OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_DESTPOS));
            SmoothTransitionToNewTarget(OwnerComp, CurrentDest, NewDest, 0.7);
            OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_PROGRESS, 0.2f);
        }
        
    }


}

FVector UBTTask_SmoothMoveTo::CalculateQuadraticBezierPoint(float t, FVector p0, FVector p1, FVector p2)
{
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;

    FVector p = uu * p0;
    p += 2 * u * t * p1;
    p += tt * p2;

    return p;
}

void UBTTask_SmoothMoveTo::SmoothTransitionToNewTarget(UBehaviorTreeComponent& OwnerComp, FVector& CurrentTarget, FVector& NewTarget, float TransitionSpeed)
{
    FVector SmoothTarget = FMath::Lerp(CurrentTarget, NewTarget, TransitionSpeed);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(BBKEY_DESTPOS, SmoothTarget);
}



