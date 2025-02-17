// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTService_DetectSpecificPlayer.h"
#include "AI/PJEAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Project_E/Character/PJECharacterShadow.h"
#include "Project_E/AI/PJEAIController.h"
#include "Project_E/AI/Enemies/Interface/PJEPlayerDectectable.h"

UBTService_DetectSpecificPlayer::UBTService_DetectSpecificPlayer()
{
    NodeName = TEXT("DetectSpecificPlayer");
    Interval = 1.0f;
}

void UBTService_DetectSpecificPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());

    if (OwnerActor)
    {
        UWorld* World = OwnerActor->GetWorld();
        TArray<AActor*> OverlappedActors;
        FVector OwnerLocation = OwnerActor->GetActorLocation();
        IPJEPlayerDectectable* PlayerDetectable = Cast<IPJEPlayerDectectable>(OwnerActor);

        float DetectionRadius = PlayerDetectable->GetPlayerDetectRange();

        UKismetSystemLibrary::SphereOverlapActors(
            World,
            OwnerLocation,
            DetectionRadius,
            TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)},
            APawn::StaticClass(),
            TArray<AActor*>(),
            OverlappedActors
        );

        bool bIsSpecificPlayerNearby = false;
        for (AActor* Actor : OverlappedActors)
        {
            APawn* Pawn = Cast<APawn>(Actor);
            if (Pawn && Pawn->IsPlayerControlled() && (Pawn == OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_PLAYERACTOR)))
            {
                FVector PlayerLocation = Pawn->GetActorLocation();
                float YDifference = PlayerLocation.Y - OwnerLocation.Y;

                // 플레이어의 Y 좌표가 OwnerActor의 Y 좌표보다 너무 아래 또는 너무 위에 있지 않을 경우에만 감지
                if (YDifference >= PlayerDetectable->GetDetectMinYDifference() && YDifference <= PlayerDetectable->GetDetectMaxYDifference())
                {
                    bIsSpecificPlayerNearby = true;
                    break;
                }
            }
        }

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, bIsSpecificPlayerNearby);
    }
}
