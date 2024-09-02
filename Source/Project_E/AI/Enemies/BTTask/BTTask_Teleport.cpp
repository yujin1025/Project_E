#include "AI/Enemies/BTTask/BTTask_Teleport.h"
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
#include "NavigationPath.h"

UBTTask_Teleport::UBTTask_Teleport()
{
    NodeName = "Random Teleport";
}

EBTNodeResult::Type UBTTask_Teleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());
    if (!OwnerController)
    {
        return EBTNodeResult::Failed;
    }

    ACharacter* Character = Cast<ACharacter>(OwnerController->GetPawn());
    if (!Character)
    {
        return EBTNodeResult::Failed;
    }

    FVector CurrentLocation = Character->GetActorLocation();

    IPJETeleportable* Teleportable = Cast<IPJETeleportable>(Character);
    float Radius = Teleportable ? Teleportable->GetTeleportRange() : 1000.0f;

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetNavigationSystem(Character->GetWorld());
    if (!NavSys)
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation RandomNavLocation;

    NavSys->GetRandomReachablePointInRadius(CurrentLocation, Radius, RandomNavLocation);

    FVector NewLocation = RandomNavLocation.Location;
    NewLocation.Z += Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    Character->SetActorLocation(NewLocation);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_PLAYERACTOR, nullptr);
    return EBTNodeResult::Succeeded;
}
