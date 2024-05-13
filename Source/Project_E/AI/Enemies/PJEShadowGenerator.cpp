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

template <typename ShadowType>
void APJEShadowGenerator::SpawnMonsterAtRandomLocation(TSubclassOf<ShadowType> MonsterClass, bool bAddToManager)
{
    if (MonsterClass)
    {
        FVector InitialSpawnLocation = FVector::ZeroVector;
        FRotator SpawnRotation = FRotator::ZeroRotator;
        ShadowType* SpawnedMonster = GetWorld()->SpawnActor<ShadowType>(MonsterClass, InitialSpawnLocation, SpawnRotation);

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
                if (bAddToManager == true) UPJEShadowGeneratorManager::GetInstance()->AddSpawnedMonster(SpawnedMonster);
            }
            else
            {
                SpawnedMonster->Destroy();
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
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APJEShadowGenerator::SpawnShadowAWithTimer, 3.0f, true);
}

void APJEShadowGenerator::SpawnShadowAWithTimer()
{
    if (UPJEShadowGeneratorManager::GetInstance()->GetShadowACount() < 3)
    {
        for (int32 i = 0; i < 3; i++) SpawnMonsterAtRandomLocation(ShadowAClass);
    }
    
    for (int32 i = 0; i < 3; i++) SpawnMonsterAtRandomLocation(ShadowBClass, false);
}
