// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowGenerator.h"
#include "Character/PJECharacterShadowA.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


UPJEShadowGeneratorManager* UPJEShadowGeneratorManager::Instance = nullptr;

UPJEShadowGeneratorManager* UPJEShadowGeneratorManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UPJEShadowGeneratorManager>(GetTransientPackage(), UPJEShadowGeneratorManager::StaticClass());
        Instance->AddToRoot();
        FWorldDelegates::LevelRemovedFromWorld.AddLambda([](ULevel* Level, UWorld* World)
            {
                UPJEShadowGeneratorManager::GetInstance()->ShutdownInstance();
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

void UPJEShadowGeneratorManager::AddShadowGenerator(APJEShadowGenerator* NewGenerator)
{
    ShadowGenerators.Add(NewGenerator);
    UpdateShadowGeneratorsCount();
}

void UPJEShadowGeneratorManager::RemoveShadowGenerator(APJEShadowGenerator* GeneratorToRemove)
{
    if (GeneratorToRemove)
    {
        ShadowGenerators.RemoveSingle(GeneratorToRemove);
        UpdateShadowGeneratorsCount();
    }
}

void UPJEShadowGeneratorManager::UpdateShadowGeneratorsCount()
{
    for (APJECharacterShadowA* Character : SpawnedShadowA)
    {
        if (Character)
        {
            Character->SetShadowGeneratorsCount(ShadowGenerators.Num());
        }
    }
}

void UPJEShadowGeneratorManager::AddSpawnedMonster(APJECharacterShadowA* SpawnedMonster)
{
    if (SpawnedMonster)
    {
        SpawnedShadowA.Add(SpawnedMonster);
    }
}

void UPJEShadowGeneratorManager::RemoveSpawnedMonster(APJECharacterShadowA* SpawnedMonsterToRemove)
{
    if (SpawnedMonsterToRemove)
    {
        SpawnedShadowA.RemoveSingle(SpawnedMonsterToRemove);
    }
}

int32 UPJEShadowGeneratorManager::GetShadowGeneratorsCount()
{
    return ShadowGenerators.Num();
}
