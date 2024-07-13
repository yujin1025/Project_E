// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_SetRandomDestPos.h"
#include "AI/PJEAI.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/Enemies/Controller/PJEShadowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetRandomDestPos::UBTTask_SetRandomDestPos()
{
}

EBTNodeResult::Type UBTTask_SetRandomDestPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        return EBTNodeResult::Failed;
    }

    FVector OriPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_ORIPOS);

    APJEShadowAIController* AIController = Cast<APJEShadowAIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        AIController->Server_SetRandomDestPos(OriPos);
    }

    return EBTNodeResult::Succeeded;
}
