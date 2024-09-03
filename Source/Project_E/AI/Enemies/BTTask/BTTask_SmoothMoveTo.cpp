// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_SmoothMoveTo.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "AI/Enemies/Controller/PJEShadowAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"

UBTTask_SmoothMoveTo::UBTTask_SmoothMoveTo()
{
	NodeName = "Smooth Move To";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SmoothMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    ACharacter* ControllingCharacter = Cast<ACharacter>(ControllingPawn);

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, 0.2f);
    return EBTNodeResult::InProgress;
}

void UBTTask_SmoothMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    APJEShadowAIController* AIController = Cast<APJEShadowAIController>(OwnerComp.GetAIOwner());
    ACharacter* Character = Cast<ACharacter>(AIController->GetPawn());
    if (Character == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
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

    NewLocation = Character->GetActorLocation() + DirVec * 100.0f;

    if (!IsFrontEmpty(Character, DirVec) || !IsLocationInNavMesh(NewLocation) || IsCliff(Character, DirVec))
    {
        AIController->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    AIController->MoveToLocation(NewLocation, 0.00001f , false, false, false, false, nullptr, true);
    BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, BlackboardComp->GetValueAsFloat(BBKEY_PROGRESS) + DeltaSeconds * 0.6);

    if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS) >= 0.9)
    {
        BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, 0.2f);
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
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
