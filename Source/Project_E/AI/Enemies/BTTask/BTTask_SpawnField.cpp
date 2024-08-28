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
    // ������ ���� ��ġ ��������
    FVector ActorLocation = OwnerActor->GetActorLocation();

    // �ݸ��� ������Ʈ�� ������� �� ��ó ��ġ ����
    float ColliderBottomOffset = 0.0f;

    // �ݸ��� ������Ʈ�� ��������
    UCapsuleComponent* CapsuleComponent = OwnerActor->FindComponentByClass<UCapsuleComponent>();
    if (CapsuleComponent)
    {
        // ĸ�� ������ ������� �ϴ� ������ ���
        ColliderBottomOffset = -CapsuleComponent->GetScaledCapsuleHalfHeight();
    }

    // ���� ���� ��ġ ����
    FVector SpawnLocation = ActorLocation + FVector(0.0f, 0.0f, ColliderBottomOffset);

    // ���� �Ķ���� ����
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = OwnerActor;

    // FieldActor ����
    APJEShadowField* FieldActor = OwnerActor->GetWorld()->SpawnActor<APJEShadowField>(FieldActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
    if (FieldActor)
    {
        // FieldActor�� OwnerActor�� �ڽ����� ����
        FieldActor->AttachToActor(OwnerActor, FAttachmentTransformRules::KeepRelativeTransform);

        FieldActor->SetActorLocation(SpawnLocation);

        // �ʵ� ���� �ʱ�ȭ
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
