#include "BTTask_SpawnField.h"
#include "AI/PJEAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "AI/Enemies/Interface/PJEFieldSpawnable.h"
#include "Project_E/AI/PJEAIController.h"
#include "AI/Enemies/PJEShadowField.h"
#include "Components/CapsuleComponent.h"

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
        TaskMemory->FieldSpawnable = Cast<IPJEFieldSpawnable>(OwnerActor);
        TaskMemory->TimeElapsed = 0.0f;

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
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;

    TaskMemory->TimeElapsed += DeltaSeconds;

    if (TaskMemory->TimeElapsed >= TaskMemory->FieldSpawnable->GetFieldDuration())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
}

void UBTTask_SpawnField::SpawnField(AActor* OwnerActor, uint8* NodeMemory)
{
    // 몬스터의 현재 위치 가져오기
    FVector ActorLocation = OwnerActor->GetActorLocation();

    // 콜리전 컴포넌트를 기반으로 발 근처 위치 조정
    float ColliderBottomOffset = 0.0f;

    // 콜리전 컴포넌트를 가져오기
    UCapsuleComponent* CapsuleComponent = OwnerActor->FindComponentByClass<UCapsuleComponent>();
    if (CapsuleComponent)
    {
        // 캡슐 범위를 기반으로 하단 오프셋 계산
        ColliderBottomOffset = -CapsuleComponent->GetScaledCapsuleHalfHeight();
    }

    // 최종 스폰 위치 설정
    FVector SpawnLocation = ActorLocation + FVector(0.0f, 0.0f, ColliderBottomOffset);

    // 스폰 파라미터 설정
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = OwnerActor;

    // FieldActor 스폰
    APJEShadowField* FieldActor = OwnerActor->GetWorld()->SpawnActor<APJEShadowField>(FieldActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (FieldActor)
    {
        // FieldActor를 OwnerActor의 자식으로 부착
        FieldActor->AttachToActor(OwnerActor, FAttachmentTransformRules::KeepRelativeTransform);

        FieldActor->SetActorLocation(SpawnLocation);

        // 필드 엑터 초기화
        FBTSpawnFieldTaskMemory* TaskMemory = (FBTSpawnFieldTaskMemory*)NodeMemory;
        FieldActor->InitializeField(
            TaskMemory->FieldSpawnable->GetFieldDuration(),
            TaskMemory->FieldSpawnable->GetDamagePerSecond(),
            TaskMemory->FieldSpawnable->GetFieldRadius()
        );
    }
}



uint16 UBTTask_SpawnField::GetInstanceMemorySize() const
{
    return sizeof(FBTSpawnFieldTaskMemory);
}
