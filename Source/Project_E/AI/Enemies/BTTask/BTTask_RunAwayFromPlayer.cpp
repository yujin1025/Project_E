// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Enemies/BTTask/BTTask_RunAwayFromPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"

UBTTask_RunAwayFromPlayer::UBTTask_RunAwayFromPlayer()
{
    NodeName = "Run Away From Player";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RunAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    APJECharacterShadowA* OwnerActor = Cast<APJECharacterShadowA>(OwnerController->GetPawn());

    FRunAwayFromPlayerTaskMemory* TaskMemory = (FRunAwayFromPlayerTaskMemory*)NodeMemory;

    TaskMemory->TargetActor = OwnerActor;
    TaskMemory->KeepMovingTime = GetWorld()->TimeSeconds;
    float RandomAngle = FMath::RandRange(-30.0f, 30.0f);
    TaskMemory->RandomDegree = RandomAngle;
    return EBTNodeResult::InProgress;
}

void UBTTask_RunAwayFromPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FRunAwayFromPlayerTaskMemory* TaskMemory = (FRunAwayFromPlayerTaskMemory*)NodeMemory;

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        UE_LOG(LogTemp, Error, TEXT("AI Controller not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ACharacter* ControlledPawn = Cast<ACharacter>(AICon->GetPawn());
    if (!ControlledPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("Controlled Pawn not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    float CurrentTime = GetWorld()->TimeSeconds;
    float KeepMovingTime = TaskMemory->KeepMovingTime;
    float MaxKeepMovingTime = TaskMemory->TargetActor->GetMaxKeepMovingTime();

    if (CurrentTime - KeepMovingTime >= MaxKeepMovingTime)
    {
        UE_LOG(LogTemp, Warning, TEXT("MaxKeepMovingTime reached: Stopping movement"));
        AICon->StopMovement();
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    AActor* PlayerActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_PLAYERACTOR));
    if (!PlayerActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Player Actor not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector PlayerPos = PlayerActor->GetActorLocation();
    FVector AIPos = ControlledPawn->GetActorLocation();
    FVector DirectionToPlayer = PlayerPos - AIPos;
    FVector DirectionAwayFromPlayer = -DirectionToPlayer.GetSafeNormal();

    
    FRotator RandomRotation = FRotator(0, TaskMemory->RandomDegree, 0);
    FVector RandomDirectionAwayFromPlayer = RandomRotation.RotateVector(DirectionAwayFromPlayer);

    FVector NewLocation = AIPos + RandomDirectionAwayFromPlayer * ControlledPawn->GetCharacterMovement()->MaxWalkSpeed * DeltaSeconds * 100.0f;

    AICon->MoveToLocation(NewLocation, 0.0001f, true, false, false, false, nullptr, true);
}
