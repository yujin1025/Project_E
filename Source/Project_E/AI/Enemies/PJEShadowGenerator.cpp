// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PJECharacterShadow.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterShadowB.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"
// Sets default values
APJEShadowGenerator::APJEShadowGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    bReplicates = true;
}

void APJEShadowGenerator::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        StartSpawnTimer();
    }
}

void APJEShadowGenerator::Server_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation, bool bAddToManager)
{
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // 지면과의 충돌을 감지하기 위해 레이캐스트를 수행
    FHitResult HitResult;
    FVector StartLocation = DesiredLocation + FVector(0.0f, 0.0f, 500.0f); // 스폰 위치 위에서 시작
    FVector EndLocation = DesiredLocation + FVector(0.0f, 0.0f, -500.0f); // 스폰 위치 아래로 레이캐스트
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params))
    {
        FVector SpawnLocation = HitResult.Location;

        // 몬스터를 스폰
        APJECharacterShadow* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadow>(MonsterClass, SpawnLocation, SpawnRotation);
        if (SpawnedMonster)
        {
            FVector BoundsExtent = SpawnedMonster->GetComponentsBoundingBox().GetExtent();
            SpawnLocation.Z += BoundsExtent.Z; // 몬스터가 지면 위에 위치하도록 Z 축을 조정
            SpawnedMonster->SetActorLocation(SpawnLocation);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn monster at DesiredLocation."));
        }
    }
    else
    {
        // 레이캐스트 실패 시
        UE_LOG(LogTemp, Warning, TEXT("Failed to find ground at DesiredLocation."));
    }
}


bool APJEShadowGenerator::Server_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation, bool bAddToManager)
{
    return true;
}

bool APJEShadowGenerator::Multicast_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager)
{
    return true;
}

void APJEShadowGenerator::Multicast_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager)
{
    
}

void APJEShadowGenerator::Destroyed()
{
    if (HasAuthority())
    {
        UPJEShadowGeneratorManager::GetInstance()->Server_RemoveShadowGenerator(this);
    }
    Super::Destroyed();
}

void APJEShadowGenerator::StartSpawnTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APJEShadowGenerator::SpawnShadowAWithTimer, 10.0f, true);
}

void APJEShadowGenerator::SpawnShadowAWithTimer()
{
    if (UPJEShadowGeneratorManager::GetInstance()->GetShadowACount() < 5)
    {
        FVector SpecificLocation = FVector(100.0f, 200.0f, 300.0f);
        for (int32 i = 0; i < 1; i++)
        {
            Server_SpawnMonster(ShadowBClass, SpecificLocation, true);
            Server_SpawnMonster(ShadowAClass, SpecificLocation, true);
        }
    }
}

void APJEShadowGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}