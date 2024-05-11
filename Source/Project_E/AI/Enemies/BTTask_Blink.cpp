// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask_Blink.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"

UBTTask_Blink::UBTTask_Blink()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Blink::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_BLINKSTARTTIME, GetWorld()->GetTimeSeconds());
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME, 0.0);
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

    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME, OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME) + DeltaSeconds);

    if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME) >= OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_SINGLEBLINKDURATION))
    {

        if (GetWorld()->TimeSeconds - OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_BLINKSTARTTIME) >= OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_BLINKDURATION))
        {
            Mesh->SetVisibility(true);
            FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
            return;
        }

        Mesh->SetVisibility(!Mesh->IsVisible());
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME, OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_ACCUMULATEDSINGLEBLINKTIME) - OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TEXT("SingleBlinkDuration")));
    }
}

