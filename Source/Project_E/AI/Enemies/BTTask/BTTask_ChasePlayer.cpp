// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_ChasePlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "AI/PJEAI.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

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

    ACharacter* Character = Cast<ACharacter>(AICon->GetPawn());
    if (!Character)
    {
        UE_LOG(LogTemp, Error, TEXT("Controlled Pawn not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector DirVec = TargetActor->GetActorLocation() - Character->GetActorLocation();
    DirVec.Normalize();

    FVector NewLocation = Character->GetActorLocation() + DirVec * 100.0f;

    if (!IsFrontEmpty(Character, DirVec) || !IsLocationInNavMesh(Character, NewLocation) || IsCliff(Character, DirVec))
    {
        AICon->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    AICon->MoveToLocation(NewLocation, 0.0001f, true, false, false, false, nullptr, true);
}
