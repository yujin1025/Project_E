// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"

// Sets default values
APJEShadowGenerator::APJEShadowGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;
}

void APJEShadowGenerator::BeginPlay()
{
    Super::BeginPlay();
    StartSpawnTimer();
}


void APJEShadowGenerator::SpawnMonsterAtRandomLocation()
{
    if (MonsterClass)
    {
        FVector SpawnLocation = GetActorLocation() + UKismetMathLibrary::RandomUnitVector() * FMath::RandRange(-SpawnRadius, SpawnRadius);
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
            APJECharacterShadowA* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadowA>(MonsterClass, SpawnLocation, FRotator::ZeroRotator);
            if (SpawnedMonster)
            {
                UPJEShadowGeneratorManager::GetInstance()->AddSpawnedMonster(SpawnedMonster);
            }
        }
    }
}

void APJEShadowGenerator::Destroyed()
{
    UPJEShadowGeneratorManager::GetInstance()->RemoveShadowGenerator(this);
    Super::Destroyed();
}


void APJEShadowGenerator::StartSpawnTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APJEShadowGenerator::SpawnMonsterWithTimer, 3.0f, true);
}

void APJEShadowGenerator::SpawnMonsterWithTimer()
{
    for (int i = 0; i < 3; i++) SpawnMonsterAtRandomLocation();
}
