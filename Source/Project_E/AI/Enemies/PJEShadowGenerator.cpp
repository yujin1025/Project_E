// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PJECharacterShadow.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterShadowB.h"
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

void APJEShadowGenerator::Server_SpawnMonsterAtRandomLocation_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, bool bAddToManager)
{
    FVector InitialSpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
    APJECharacterShadow* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadow>(MonsterClass, InitialSpawnLocation, SpawnRotation);

    if (SpawnedMonster)
    {
        FVector RandomOffset = UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(-SpawnedMonster->GetShadowSpawnRadius(), SpawnedMonster->GetShadowSpawnRadius());
        RandomOffset.Z = 0.0f;
        FVector SpawnLocation = GetActorLocation() + RandomOffset;
        SpawnLocation.Z += 500.0f;

        FHitResult HitResult;
        FVector StartLocation = SpawnLocation;
        FVector EndLocation = StartLocation;
        EndLocation.Z -= 1000.0f;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params))
        {
            SpawnLocation = HitResult.Location;
            FVector BoundsExtent = SpawnedMonster->GetComponentsBoundingBox().GetExtent();
            SpawnLocation.Z += BoundsExtent.Z;
            SpawnedMonster->SetActorLocation(SpawnLocation);
            Multicast_SpawnMonsterAtRandomLocation(MonsterClass, SpawnLocation, bAddToManager);
        }
        else
        {
            SpawnedMonster->Destroy();
        }
    }
}

bool APJEShadowGenerator::Server_SpawnMonsterAtRandomLocation_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, bool bAddToManager)
{
    return true;
}

void APJEShadowGenerator::Multicast_SpawnMonsterAtRandomLocation_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager)
{
    FVector InitialSpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
    APJECharacterShadow* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadow>(MonsterClass, InitialSpawnLocation, SpawnRotation);

    if (SpawnedMonster)
    {
        SpawnedMonster->SetActorLocation(SpawnLocation);
        if (bAddToManager)
        {
            UPJEShadowGeneratorManager::GetInstance()->Server_AddSpawnedMonster(SpawnedMonster);
        }
    }
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
    if (UPJEShadowGeneratorManager::GetInstance()->GetShadowACount() < 20)
    {
        for (int32 i = 0; i < 3; i++)
        {
            Server_SpawnMonsterAtRandomLocation(ShadowBClass, false);
            Server_SpawnMonsterAtRandomLocation(ShadowAClass, false);
        }
    }
}

void APJEShadowGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}