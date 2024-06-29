// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTService_Detect.h"
#include "AI/PJEAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Project_E/Character/PJECharacterShadow.h"
#include "Project_E/AI/PJEAIController.h"
#include "Project_E/AI/Enemies/Interface/PJEPlayerDectectable.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());

    if (OwnerActor)
    {
        UWorld* World = OwnerActor->GetWorld();
        TArray<AActor*> OverlappedActors;
        FVector AIControllerLocation = OwnerActor->GetActorLocation();
        IPJEPlayerDectectable* PlayerDetectable = Cast<IPJEPlayerDectectable>(OwnerActor);

        float DetectionRadius = PlayerDetectable->GetPlayerDetectRange();
        

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
        AActor* PlayerActor = nullptr;
        for (AActor* Actor : OverlappedActors)
        {
            APawn* Pawn = Cast<APawn>(Actor);
            if (Pawn && Pawn->IsPlayerControlled())
            {
                bIsPlayerNearby = true;
                PlayerActor = Actor;
                break;
            }
        }

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, bIsPlayerNearby);
        if (PlayerActor != nullptr)
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_PLAYERACTOR, PlayerActor);
    }

}
