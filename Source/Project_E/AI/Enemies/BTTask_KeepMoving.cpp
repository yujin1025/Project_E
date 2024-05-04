// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_KeepMoving.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NavigationSystem.h"

UBTTask_KeepMoving::UBTTask_KeepMoving(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    NodeName = "Move In Direction";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_KeepMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    StartTime = GetWorld()->TimeSeconds;
    return EBTNodeResult::InProgress;
}

void UBTTask_KeepMoving::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ACharacter* ControlledPawn = Cast<ACharacter>(AICon->GetPawn());
    if (!ControlledPawn)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector Direction = ControlledPawn->GetActorForwardVector();
    FVector NewLocation = ControlledPawn->GetActorLocation() + Direction * ControlledPawn->GetCharacterMovement()->MaxWalkSpeed * DeltaSeconds * 100;
    AICon->MoveToLocation(NewLocation, 0.0001f, true, false, false, false, nullptr, true);
    
    if (GetWorld()->TimeSeconds - StartTime >= 2.0f)
    {
        AICon->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}
