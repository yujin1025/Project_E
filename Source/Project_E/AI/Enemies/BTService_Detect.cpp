// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTService_Detect.h"
#include "AI/PJEAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* AIControllerPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (AIControllerPawn)
    {
        UWorld* World = AIControllerPawn->GetWorld();
        TArray<AActor*> OverlappedActors;
        float DetectionRadius = 300.0f;
        FVector AIControllerLocation = AIControllerPawn->GetActorLocation();

        UKismetSystemLibrary::SphereOverlapActors(
            World,
            AIControllerLocation,
            DetectionRadius,
            TArray<TEnumAsByte<EObjectTypeQuery>>{UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)},
            APawn::StaticClass(),
            TArray<AActor*>(),
            OverlappedActors
        );

        bool bIsPlayerNearby = false;
        for (AActor* Actor : OverlappedActors)
        {
            APawn* Pawn = Cast<APawn>(Actor);
            if (Pawn && Pawn->IsPlayerControlled())
            {
                bIsPlayerNearby = true;
                break;
            }
        }

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bIsPlayerNearby);
    }

}
