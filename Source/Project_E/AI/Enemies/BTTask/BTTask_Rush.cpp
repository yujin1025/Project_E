// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_Rush.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/Enemies/Interface/PJERushable.h"

UBTTask_Rush::UBTTask_Rush()
{
    NodeName = "Rush";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Rush::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

    FBTRushTaskMemory* TaskMemory = (FBTRushTaskMemory*)NodeMemory;

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter* ControlledCharacter = Cast<ACharacter>(AIController->GetPawn());
    if (!ControlledCharacter)
    {
        return EBTNodeResult::Failed;
    }

    IPJERushable* Rushable = Cast<IPJERushable>(AIController->GetPawn());
    if (!Rushable)
    {
        return EBTNodeResult::Failed;
    }

    FVector CurrentLocation = ControlledCharacter->GetActorLocation();
    FVector ForwardDirection = ControlledCharacter->GetActorForwardVector();
    FVector TargetLocation = CurrentLocation + (ForwardDirection * Rushable->GetRushDistance());

    TaskMemory->TargetLocation = TargetLocation;

    ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = Rushable->GetRushSpeed();

    return EBTNodeResult::InProgress;
}

void UBTTask_Rush::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FBTRushTaskMemory* TaskMemory = (FBTRushTaskMemory*)NodeMemory;

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ACharacter* ControlledCharacter = Cast<ACharacter>(AIController->GetPawn());
    if (!ControlledCharacter)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector TargetLocation = TaskMemory->TargetLocation;
    FVector CurrentLocation = ControlledCharacter->GetActorLocation();

    // 목표 위치에 도달했는지 확인
    if (FVector::Dist(CurrentLocation, TargetLocation) <= 1.0f)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else
    {
        // 목표 위치로 이동
        AIController->MoveToLocation(TargetLocation, 1.0f, false);
    }
}

uint16 UBTTask_Rush::GetInstanceMemorySize() const
{
    return sizeof(FBTRushTaskMemory);
}
