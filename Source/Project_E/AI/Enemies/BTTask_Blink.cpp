// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Blink.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_Blink::UBTTask_Blink()
{
	bNotifyTick = true;
    StartTime = 0;
    AccumulatedTime = 0.0f;
}

EBTNodeResult::Type UBTTask_Blink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	StartTime = GetWorld()->GetTimeSeconds();
    AccumulatedTime = 0.0f;
	return EBTNodeResult::InProgress;
}

void UBTTask_Blink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

    USkeletalMeshComponent* Mesh = ControlledPawn->GetMesh();

    AccumulatedTime += DeltaSeconds;

    if (AccumulatedTime >= FlashDuration)
    {

        if (GetWorld()->TimeSeconds - StartTime >= 0.2f)
        {
            Mesh->SetVisibility(true);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return;
        }

        Mesh->SetVisibility(!Mesh->IsVisible());
        AccumulatedTime -= FlashDuration;
    }
}

