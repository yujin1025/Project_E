// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowGenerator.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterShadowB.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UPJEShadowGeneratorManager* UPJEShadowGeneratorManager::Instance = nullptr;

UPJEShadowGeneratorManager* UPJEShadowGeneratorManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UPJEShadowGeneratorManager>(GetTransientPackage(), UPJEShadowGeneratorManager::StaticClass());
        Instance->AddToRoot();
        FWorldDelegates::LevelRemovedFromWorld.AddLambda([](ULevel* Level, UWorld* World)
            {
                ShutdownInstance();
            });

        FWorldDelegates::OnWorldCleanup.AddLambda([](UWorld* World, bool bSessionEnded, bool bCleanupResources)
            {
                ShutdownInstance();
            });
        Instance->FindAllShadowGenerators();
    }
    return Instance;
}

void UPJEShadowGeneratorManager::ShutdownInstance()
{
    if (Instance)
    {
        Instance->RemoveFromRoot();
        Instance = nullptr;
    }
}


void UPJEShadowGeneratorManager::FindAllShadowGenerators()
{
    ShadowGenerators.Empty();

    if (GEngine)
    {
        if (GWorld)
        {
            for (TActorIterator<APJEShadowGenerator> It(GWorld); It; ++It)
            {
                APJEShadowGenerator* ShadowGenerator = *It;
                if (ShadowGenerator)
                {
                    ShadowGenerators.Add(ShadowGenerator);
                }
            }
        }
    }
}

void UPJEShadowGeneratorManager::Server_AddShadowGenerator_Implementation(APJEShadowGenerator* NewGenerator)
{
    ShadowGenerators.Add(NewGenerator);
    UpdateShadowGeneratorsCount();
}

bool UPJEShadowGeneratorManager::Server_AddShadowGenerator_Validate(APJEShadowGenerator* NewGenerator)
{
    return true;
}

void UPJEShadowGeneratorManager::Server_RemoveShadowGenerator_Implementation(APJEShadowGenerator* GeneratorToRemove)
{
    if (GeneratorToRemove)
    {
        ShadowGenerators.RemoveSingle(GeneratorToRemove);
        UpdateShadowGeneratorsCount();
    }
}

bool UPJEShadowGeneratorManager::Server_RemoveShadowGenerator_Validate(APJEShadowGenerator* GeneratorToRemove)
{
    return true;
}

void UPJEShadowGeneratorManager::Server_AddSpawnedMonster_Implementation(APJECharacterShadow* SpawnedMonster)
{
    if (SpawnedMonster)
    {
        APJECharacterShadowA* SpawnedShadowA = Cast<APJECharacterShadowA>(SpawnedMonster);
        if (SpawnedShadowA != nullptr)
        {
            SpawnedShadowAArr.Add(SpawnedShadowA);
        }
        else
        {
            APJECharacterShadowB* SpawnedShadowB = Cast<APJECharacterShadowB>(SpawnedMonster);
            if (SpawnedShadowB != nullptr)
            {
                SpawnedShadowBArr.Add(SpawnedShadowB);
            }
        }
    }
}

bool UPJEShadowGeneratorManager::Server_AddSpawnedMonster_Validate(APJECharacterShadow* SpawnedMonster)
{
    return true;
}

void UPJEShadowGeneratorManager::Server_RemoveSpawnedMonster_Implementation(APJECharacterShadow* SpawnedMonsterToRemove)
{
    if (SpawnedMonsterToRemove)
    {
        APJECharacterShadowA* SpawnedShadowA = Cast<APJECharacterShadowA>(SpawnedMonsterToRemove);
        if (SpawnedShadowA != nullptr)
        {
            SpawnedShadowAArr.RemoveSingle(SpawnedShadowA);
        }
        else
        {
            APJECharacterShadowB* SpawnedShadowB = Cast<APJECharacterShadowB>(SpawnedMonsterToRemove);
            if (SpawnedShadowB != nullptr)
            {
                SpawnedShadowBArr.RemoveSingle(SpawnedShadowB);
            }
        }
    }
}

bool UPJEShadowGeneratorManager::Server_RemoveSpawnedMonster_Validate(APJECharacterShadow* SpawnedMonsterToRemove)
{
    return true;
}

void UPJEShadowGeneratorManager::OnRep_ShadowGenerators()
{
    UpdateShadowGeneratorsCount();
}

void UPJEShadowGeneratorManager::OnRep_SpawnedShadowAArr()
{
    UpdateShadowGeneratorsCount();
}

void UPJEShadowGeneratorManager::OnRep_SpawnedShadowBArr()
{
    UpdateShadowGeneratorsCount();
}

void UPJEShadowGeneratorManager::UpdateShadowGeneratorsCount()
{
    for (APJECharacterShadowA* Character : SpawnedShadowAArr)
    {
        if (Character)
        {
            Character->SetShadowGeneratorsCount(ShadowGenerators.Num());
        }
    }
}

int32 UPJEShadowGeneratorManager::GetShadowGeneratorsCount() const
{
    return ShadowGenerators.Num();
}

int32 UPJEShadowGeneratorManager::GetShadowACount() const
{
    return SpawnedShadowAArr.Num();
}

void UPJEShadowGeneratorManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UPJEShadowGeneratorManager, ShadowGenerators);
    DOREPLIFETIME(UPJEShadowGeneratorManager, SpawnedShadowAArr);
    DOREPLIFETIME(UPJEShadowGeneratorManager, SpawnedShadowBArr);
}