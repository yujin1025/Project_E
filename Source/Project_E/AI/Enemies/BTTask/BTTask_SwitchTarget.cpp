// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_SwitchTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SwitchTarget::UBTTask_SwitchTarget()
{
    NodeName = "Switch Target";
}

EBTNodeResult::Type UBTTask_SwitchTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp)
    {
        return EBTNodeResult::Failed;
    }

    AActor* CurrentTarget = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("PlayerActor")));

    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), Players);

    if (Players.Num() == 0)
    {
        return EBTNodeResult::Failed;
    }

    AActor* NewTarget = GetRandomPlayerActor(Players, CurrentTarget);

    BlackboardComp->SetValueAsObject(TEXT("PlayerActor"), NewTarget);

    return EBTNodeResult::Succeeded;
}

AActor* UBTTask_SwitchTarget::GetRandomPlayerActor(const TArray<AActor*>& Players, AActor* CurrentTarget)
{
    TArray<AActor*> ValidPlayers = Players.FilterByPredicate([CurrentTarget](AActor* Player) {
        return Player != CurrentTarget;
        });

    if (ValidPlayers.Num() == 0)
    {
        return CurrentTarget;
    }

    int32 RandomIndex = FMath::RandRange(0, ValidPlayers.Num() - 1);
    return ValidPlayers[RandomIndex];
}
