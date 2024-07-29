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
    return EBTNodeResult::InProgress;
}

void UBTTask_SmoothMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ControllingPawn)
    {
        return;
    }

    APJEShadowAIController* AIController = Cast<APJEShadowAIController>(OwnerComp.GetAIOwner());
    ACharacter* Character = Cast<ACharacter>(AIController->GetPawn());
    if (Character == nullptr)
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
    if (nullptr == NavSystem)
    {
        return;
    }

    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
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

    // 충돌 검사
    FVector Start = Character->GetActorLocation();
    FVector End = Start + DirVec * 100.0f;
    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

    // 낭떠러지 검사
    FVector DownStart = Start + DirVec * 100.0f;
    FVector DownEnd = Start + DirVec * 100.0f + FVector(0.0f, 0.0f, -200.0f);
    FHitResult DownHitResult;
    bool bDownHit = GetWorld()->LineTraceSingleByChannel(DownHitResult, DownStart, DownEnd, ECC_Visibility);

    if (bHit || !bDownHit)
    {
        // 충돌 또는 낭떠러지 시 태스크 실패로 설정
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    AIController->MoveToLocation(Character->GetActorLocation() + DirVec * 10.0f, -1.0f, false, false, false, false, nullptr, true);
    BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, BlackboardComp->GetValueAsFloat(BBKEY_PROGRESS) + DeltaSeconds * 0.6);

    if (OwnerComp.GetBlackboardComponent()->GetValueAsFloat(BBKEY_PROGRESS) >= 0.9)
    {
        BlackboardComp->SetValueAsFloat(BBKEY_PROGRESS, 0.2f);
        if (AIController)
        {
            FVector DestPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(BBKEY_DESTPOS);
            AIController->Server_SetRandomDestPos(DestPos);
        }
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
