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
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "AI/Enemies/Interface/PJEFieldSpawnable.h"
#include "Project_E/AI/PJEAIController.h"

UBTTask_SpawnField::UBTTask_SpawnField()
{
    NodeName = "Spawn Field";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_SpawnField::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());
    if (OwnerActor)
    {
        FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;
        TaskMemory->TimeElapsed = 0.0f;
        TaskMemory->DamageElapsedTime = 0.0f;  // Initialize damage elapsed time
        TaskMemory->FieldMesh = nullptr;
        TaskMemory->OverlappingActors.Empty();
        TaskMemory->FieldSpawnable = Cast<IPJEFieldSpawnable>(OwnerActor);
        
        if (TaskMemory->FieldSpawnable == nullptr)
        {
            UE_LOG(LogTemp, Error, TEXT("Cast Failed"));
        }

        SpawnField(OwnerActor, NodeMemory);
        return EBTNodeResult::InProgress;
    }
    return EBTNodeResult::Failed;
}

void UBTTask_SpawnField::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;
    TaskMemory->TimeElapsed += DeltaSeconds;
    TaskMemory->DamageElapsedTime += DeltaSeconds;

    AActor* OwnerActor = OwnerComp.GetOwner();
    if (!OwnerActor)
    {
        DestroyField(OwnerComp, NodeMemory);
        return;
    }

    AController* Controller = Cast<AController>(OwnerActor);
    APawn* ControlledPawn = Controller ? Controller->GetPawn() : nullptr;
    FVector Location = ControlledPawn ? ControlledPawn->GetActorLocation() : OwnerActor->GetActorLocation();

    if (TaskMemory->TimeElapsed >= TaskMemory->FieldSpawnable->GetFieldDuration() + 2.0f)
    {
        DestroyField(OwnerComp, NodeMemory);
    }
    else if (TaskMemory->TimeElapsed > 2.0f)
    {
        float ShrinkTime = TaskMemory->TimeElapsed - 2.0f;
        float ShrinkFactor = FMath::Clamp(1.0f - (ShrinkTime / TaskMemory->FieldSpawnable->GetFieldDuration()), 0.0f, 1.0f);
        FVector NewScale = FVector(TaskMemory->FieldSpawnable->GetFieldRadius() / 50.0f) * ShrinkFactor;
        TaskMemory->FieldMesh->SetWorldScale3D(NewScale);

        DrawDebugSphere(GetWorld(), Location, TaskMemory->FieldSpawnable->GetFieldRadius() * ShrinkFactor, 32, FColor::Green, false, -1.0f, 0, 5.0f);
    }
    else
    {
        DrawDebugSphere(GetWorld(), Location, TaskMemory->FieldSpawnable->GetFieldRadius(), 32, FColor::Green, false, -1.0f, 0, 5.0f);
    }

    UpdateOverlappingActors(Location, NodeMemory);

    if (TaskMemory->DamageElapsedTime >= 1.0f)
    {
        DealDamage(nullptr, NodeMemory);
        TaskMemory->DamageElapsedTime = 0.0f;
    }
}

void UBTTask_SpawnField::UpdateOverlappingActors(const FVector& Location, uint8* NodeMemory)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    TArray<FOverlapResult> OverlapResults;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TaskMemory->FieldSpawnable->GetFieldRadius());

    TaskMemory->OverlappingActors.Empty(); // 기존 목록 초기화
    GetWorld()->OverlapMultiByChannel(OverlapResults, Location, FQuat::Identity, ECC_WorldDynamic, CollisionShape);

    for (const FOverlapResult& Result : OverlapResults)
    {
        if (AActor* OverlappedActor = Result.GetActor())
        {
            TaskMemory->OverlappingActors.Add(OverlappedActor);
        }
    }
}

void UBTTask_SpawnField::SpawnField(AActor* OwnerActor, uint8* NodeMemory)
{
    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    TaskMemory->FieldMesh = NewObject<UStaticMeshComponent>(OwnerActor);
    TaskMemory->FieldMesh->AttachToComponent(OwnerActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    TaskMemory->FieldMesh->SetWorldScale3D(FVector(TaskMemory->FieldSpawnable->GetFieldRadius() / 50.0f));
    TaskMemory->FieldMesh->RegisterComponent();

    AController* Controller = Cast<AController>(OwnerActor);
    APawn* ControlledPawn = Controller ? Controller->GetPawn() : nullptr;
    FVector Location = ControlledPawn ? ControlledPawn->GetActorLocation() : OwnerActor->GetActorLocation();

    //DrawDebugSphere(GetWorld(), Location, Radius, 32, FColor::Green, false, Duration + 2.0f, 0, 5.0f);

    TArray<FOverlapResult> OverlapResults;
    FCollisionShape CollisionShape = FCollisionShape::MakeSphere(TaskMemory->FieldSpawnable->GetFieldRadius());
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
        if (Actor->IsA(APJECharacterPlayer::StaticClass()))
        {
            UGameplayStatics::ApplyDamage(Actor, TaskMemory->FieldSpawnable->GetDamagePerSecond(), nullptr, DamagedActor, nullptr);
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
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

uint16 UBTTask_SpawnField::GetInstanceMemorySize() const
{
    return sizeof(FBTSpawnFieldTaskMemory);
}
