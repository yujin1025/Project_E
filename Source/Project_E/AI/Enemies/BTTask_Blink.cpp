// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Blink.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_Blink::UBTTask_Blink()
{
	bNotifyTick = true;
	FlashCount = 0;
    StartTime = 0;
}

EBTNodeResult::Type UBTTask_Blink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	StartTime = GetWorld()->GetTimeSeconds();
	FlashCount = 0;
    AccumulatedTime = 0.0f;
	return EBTNodeResult::InProgress;
}

void UBTTask_Blink::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
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

    const float FlashDuration = 0.2/4.0;  

    AccumulatedTime += DeltaSeconds;

    if (AccumulatedTime >= FlashDuration)
    {
        FlashCount++;
        Mesh->SetVisibility(!Mesh->IsVisible());

        if (FlashCount >= 4)
        {
            Mesh->SetVisibility(true);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return;
        }

        AccumulatedTime -= FlashDuration;
    }
}

