// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_TeleportNearPlayer.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"
#include "Project_E/AI/Enemies/Interface/PJETeleportable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"

UBTTask_TeleportNearPlayer::UBTTask_TeleportNearPlayer()
{
	NodeName = "Random Teleport Near Player";
}

EBTNodeResult::Type UBTTask_TeleportNearPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());
    FVector CurrentLocation = OwnerActor->GetActorLocation();
    FNavLocation RandomNavLocation;

    IPJETeleportable* Teleportable = Cast<IPJETeleportable>(OwnerActor);
    float Radius = Teleportable->GetTeleportRange();

    UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    const int32 MaxAttempts = 10;  // 시도 횟수 제한
    int32 Attempts = 0;
    bool bLocationFound = false;

    AActor* PlayerActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_PLAYERACTOR));
    while (Attempts < MaxAttempts)
    {
        if (NavSys->GetRandomPointInNavigableRadius(PlayerActor->GetActorLocation(), Radius, RandomNavLocation))
        {
            // 라인 트레이스로 지형 위에 있는지 확인
            FVector TraceStart = RandomNavLocation.Location + FVector(0, 0, 100.0f);
            FVector TraceEnd = RandomNavLocation.Location - FVector(0, 0, 200.0f);

            FHitResult HitResult;
            bool bHit = UKismetSystemLibrary::LineTraceSingle(
                this,
                TraceStart,
                TraceEnd,
                UEngineTypes::ConvertToTraceType(ECC_Visibility),
                false,
                TArray<AActor*>(),
                EDrawDebugTrace::ForDuration,
                HitResult,
                true
            );

            if (bHit)
            {
                // 충돌된 위치를 최종 위치로 사용
                RandomNavLocation.Location = HitResult.Location;

                // 만약 OwnerActor가 캐릭터라면 캡슐 컴포넌트를 고려하여 위치를 조정
                ACharacter* Character = Cast<ACharacter>(OwnerActor);
                if (Character)
                {
                    float HalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
                    RandomNavLocation.Location.Z += HalfHeight;
                }

                bLocationFound = true;
                break;
            }
        }

        Attempts++;
    }

    if (!bLocationFound)
    {
        return EBTNodeResult::Failed;
    }

    OwnerActor->SetActorLocation(RandomNavLocation.Location);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_PLAYERACTOR, nullptr);
    return EBTNodeResult::Succeeded;
}
