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
#include "AI/Enemies/PJEShadowArea.h"

// Sets default values
APJEShadowGenerator::APJEShadowGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    bReplicates = true;

    CurrentCount = 0;
}

void APJEShadowGenerator::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        StartSpawnTimer();
    }
}

void APJEShadowGenerator::Server_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation)
{
    if (MaxCount > CurrentCount)
    {
        FRotator SpawnRotation = FRotator::ZeroRotator;

        APJECharacterShadow* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadow>(MonsterClass, DesiredLocation, SpawnRotation);
        if (SpawnedMonster)
        {
            if (SpawnedMonster->IsA(APJECharacterShadowA::StaticClass()))
            {
                APJECharacterShadowA* ShadowA = Cast<APJECharacterShadowA>(SpawnedMonster);
                ShadowA->SetShadowArea(ShadowArea);
                ShadowArea->ShadowAArr.Add(ShadowA);
                CurrentCount++;
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn monster at DesiredLocation."));
        }
    }
}


bool APJEShadowGenerator::Server_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation)
{
    return true;
}

void APJEShadowGenerator::Destroyed()
{
    if (ShadowArea)
    {
        ShadowArea->ShadowGeneratorArr.Remove(this);
        ShadowArea->SetBackgroundVolume(ShadowArea->ShadowGeneratorArr.Num());
    }
    Super::Destroyed();
}

void APJEShadowGenerator::StartSpawnTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APJEShadowGenerator::SpawnShadowAWithTimer, 10.0f, true);
}

void APJEShadowGenerator::SpawnShadowAWithTimer()
{
    for (int32 i = 0; i < 1; i++)
    {
        Server_SpawnMonster(ShadowBClass, SpawnPos);
        Server_SpawnMonster(ShadowAClass, SpawnPos);

        if (ShadowArea && ShadowArea->GetIsPlayerInArea())
        {
            ShadowArea->PlayShadowASound();
        }
    }
}

void APJEShadowGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
