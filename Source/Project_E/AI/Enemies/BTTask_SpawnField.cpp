#include "BTTask_SpawnField.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "AI/PJEAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SpawnField::UBTTask_SpawnField()
{
    NodeName = "Spawn Field";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SpawnField::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AActor* OwnerActor = OwnerComp.GetOwner();
    if (OwnerActor)
    {
        FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;
        TaskMemory->TimeElapsed = 0.0f;
        TaskMemory->FieldMesh = nullptr;
        TaskMemory->OverlappingActors.Empty();

        SpawnField(OwnerActor, NodeMemory);
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTask_SpawnField::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;
    TaskMemory->TimeElapsed += DeltaSeconds;

    AActor* OwnerActor = OwnerComp.GetOwner();
    if (!OwnerActor)
    {
        DestroyField(OwnerComp, NodeMemory);
        return;
    }

    AController* Controller = Cast<AController>(OwnerActor);
    APawn* ControlledPawn = Controller ? Controller->GetPawn() : nullptr;
    FVector Location = ControlledPawn ? ControlledPawn->GetActorLocation() : OwnerActor->GetActorLocation();

    if (TaskMemory->TimeElapsed >= Duration + 2.0f)
    {
        DestroyField(OwnerComp, NodeMemory);
    }
    else if (TaskMemory->TimeElapsed > 2.0f)
    {
        float ShrinkTime = TaskMemory->TimeElapsed - 2.0f;
        float ShrinkFactor = FMath::Clamp(1.0f - (ShrinkTime / Duration), 0.0f, 1.0f);
        FVector NewScale = FVector(Radius / 50.0f) * ShrinkFactor;
        TaskMemory->FieldMesh->SetWorldScale3D(NewScale);

        DrawDebugSphere(GetWorld(), Location, Radius * ShrinkFactor, 32, FColor::Green, false, -1.0f, 0, 5.0f);
    }
    else
    {
        DrawDebugSphere(GetWorld(), Location, Radius, 32, FColor::Green, false, -1.0f, 0, 5.0f);
    }

    DealDamage(nullptr, NodeMemory);
}

void UBTTask_SpawnField::SpawnField(AActor* OwnerActor, uint8* NodeMemory)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    TaskMemory->FieldMesh = NewObject<UStaticMeshComponent>(OwnerActor);
    TaskMemory->FieldMesh->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    TaskMemory->FieldMesh->SetWorldScale3D(FVector(Radius / 50.0f));
    TaskMemory->FieldMesh->RegisterComponent();

    AController* Controller = Cast<AController>(OwnerActor);
    APawn* ControlledPawn = Controller ? Controller->GetPawn() : nullptr;
    FVector Location = ControlledPawn ? ControlledPawn->GetActorLocation() : OwnerActor->GetActorLocation();

    //DrawDebugSphere(GetWorld(), Location, Radius, 32, FColor::Green, false, Duration + 2.0f, 0, 5.0f);

    TArray<FOverlapResult> OverlapResults;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(Radius);
    GetWorld()->OverlapMultiByChannel(OverlapResults, Location, FQuat::Identity, ECC_WorldDynamic, CollisionShape);

    for (const FOverlapResult& Result : OverlapResults)
    {
        if (AActor* OverlappedActor = Result.GetActor())
        {
            TaskMemory->OverlappingActors.Add(OverlappedActor);
        }
    }
}

void UBTTask_SpawnField::DealDamage(AActor* DamagedActor, uint8* NodeMemory)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    for (AActor* Actor : TaskMemory->OverlappingActors)
    {
        if (Actor->IsA(ACharacter::StaticClass()))
        {
            UGameplayStatics::ApplyDamage(Actor, DamagePerSecond, nullptr, DamagedActor, nullptr);
        }
    }
}

void UBTTask_SpawnField::DestroyField(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    if (TaskMemory->FieldMesh)
    {
        TaskMemory->FieldMesh->DestroyComponent();
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(BBKEY_ISPLAYERNEARBY, false);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UBTTask_SpawnField::OnGameplayTaskActivated(UGameplayTask& Task)
{
    // Do nothing
}

uint16 UBTTask_SpawnField::GetInstanceMemorySize() const
{
    return sizeof(FBTSpawnFieldTaskMemory);
}
