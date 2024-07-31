#include "AI/Enemies/BTTask/BTTask_RunAwayFromPlayer.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/PJEAI.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Project_E/Character/PJECharacterShadowA.h"
#include "Project_E/AI/PJEAIController.h"
#include "DrawDebugHelpers.h"

UBTTask_RunAwayFromPlayer::UBTTask_RunAwayFromPlayer()
{
    NodeName = "Run Away From Player";
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RunAwayFromPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    APJEAIController* OwnerController = Cast<APJEAIController>(OwnerComp.GetOwner());

    AActor* OwnerActor = Cast<AActor>(OwnerController->GetPawn());

    FRunAwayFromPlayerTaskMemory* TaskMemory = (FRunAwayFromPlayerTaskMemory*)NodeMemory;

    APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
    ACharacter* ControllingCharacter = Cast<ACharacter>(ControllingPawn);

    TaskMemory->RunAwayable = Cast<IPJERunAwayable>(OwnerActor);
    TaskMemory->KeepMovingTime = GetWorld()->TimeSeconds;
    float RandomAngle = FMath::RandRange(-30.0f, 30.0f);
    TaskMemory->RandomDegree = RandomAngle;
    TaskMemory->LastMaxMoveSpeed = ControllingCharacter->GetCharacterMovement()->MaxWalkSpeed;

    ControllingCharacter->GetCharacterMovement()->MaxWalkSpeed = TaskMemory->RunAwayable->GetRunAwaySpeed();
    return EBTNodeResult::InProgress;
}

void UBTTask_RunAwayFromPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

    FRunAwayFromPlayerTaskMemory* TaskMemory = (FRunAwayFromPlayerTaskMemory*)NodeMemory;

    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        UE_LOG(LogTemp, Error, TEXT("AI Controller not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    ACharacter* ControlledPawn = Cast<ACharacter>(AICon->GetPawn());
    if (!ControlledPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("Controlled Pawn not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    float CurrentTime = GetWorld()->TimeSeconds;
    float KeepMovingTime = TaskMemory->KeepMovingTime;
    float MaxKeepMovingTime = TaskMemory->RunAwayable->GetMaxKeepMovingTime();

    if (CurrentTime - KeepMovingTime >= MaxKeepMovingTime)
    {
        AICon->StopMovement();
        ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = TaskMemory->LastMaxMoveSpeed;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    AActor* PlayerActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_PLAYERACTOR));
    if (!PlayerActor)
    {
        UE_LOG(LogTemp, Error, TEXT("Player Actor not found"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
        return;
    }

    FVector PlayerPos = PlayerActor->GetActorLocation();
    FVector AIPos = ControlledPawn->GetActorLocation();
    FVector DirectionToPlayer = PlayerPos - AIPos;
    FVector DirectionAwayFromPlayer = -DirectionToPlayer.GetSafeNormal();

    FRotator RandomRotation = FRotator(0, TaskMemory->RandomDegree, 0);
    FVector RandomDirectionAwayFromPlayer = RandomRotation.RotateVector(DirectionAwayFromPlayer);
    RandomDirectionAwayFromPlayer.Normalize();

    FVector NewLocation = AIPos + RandomDirectionAwayFromPlayer * ControlledPawn->GetCharacterMovement()->MaxWalkSpeed * DeltaSeconds * 100.0f;

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(ControlledPawn);

    FVector Start = ControlledPawn->GetActorLocation();
    FVector End = Start + RandomDirectionAwayFromPlayer * 100.0f;
    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);

    FVector DownStart = End;
    FVector DownEnd = End + FVector(0.0f, 0.0f, -200.0f);
    FHitResult DownHitResult;
    bool bDownHit = GetWorld()->LineTraceSingleByChannel(DownHitResult, DownStart, DownEnd, ECC_Visibility, CollisionParams);

    if (bHit || !bDownHit)
    {  
        AICon->StopMovement();
        ControlledPawn->GetCharacterMovement()->MaxWalkSpeed = TaskMemory->LastMaxMoveSpeed;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
        return;
    }

    AICon->MoveToLocation(NewLocation, 0.0001f, true, false, false, false, nullptr, true);
}

uint16 UBTTask_RunAwayFromPlayer::GetInstanceMemorySize() const
{
    return sizeof(FRunAwayFromPlayerTaskMemory);
}
