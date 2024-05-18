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
    ACharacter* Character = Cast<ACharacter>(AIController->GetPawn());
    if (Character == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (nullptr == NavSystem)
    {
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        return;
    }
        

    FVector NewLocation = CalculateQuadraticBezierPoint(
        BlackboardComp->GetValueAsFloat(BBKEY_PROGRESS),
        Character->GetActorLocation(),
        BlackboardComp->GetValueAsVector(BBKEY_SUBDESTPOS),
        BlackboardComp->GetValueAsVector(BBKEY_DESTPOS)
    );

    FVector DirVec = NewLocation - Character->GetActorLocation();
    DirVec.Normalize();
    AIController->MoveToLocation(Character->GetActorLocation() + DirVec * 100.0f, -1.0f, false, false, false, false, nullptr, true);
    BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, BlackboardComp->GetValueAsFloat(BBKEY_PROGRESS) + DeltaSeconds * 0.4);

    if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS) >= 0.9)
    {
        
        FVector CurrentDest = BlackboardComp->GetValueAsVector(BBKEY_DESTPOS);
        FNavLocation NextPatrolPos;
        if (NavSystem->GetRandomPointInNavigableRadius(CurrentDest, 3000.0f, NextPatrolPos))
        {
            FVector NewDest = NextPatrolPos.Location;
            
            BlackboardComp->SetValueAsVector(BBKEY_SUBDESTPOS, BlackboardComp->GetValueAsVector(BBKEY_DESTPOS));
            BlackboardComp->SetValueAsVector(BBKEY_DESTPOS, NewDest);
            BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, 0.2f);
        }
    }
}

FVector UBTTask_SmoothMoveTo::CalculateQuadraticBezierPoint(float CurrentProgress, FVector Pos0, FVector Pos1, FVector Pos2)
{
    float U = 1 - CurrentProgress;
    float SquaredCurrentProgress = CurrentProgress * CurrentProgress;
    float SquaredU = U * U;

    FVector NewPos = SquaredU * Pos0;
    NewPos += 2 * U * CurrentProgress * Pos1;
    NewPos += SquaredCurrentProgress * Pos2;

    return NewPos;
}
