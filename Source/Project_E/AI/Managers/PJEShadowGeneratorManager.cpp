// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowGenerator.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterShadowB.h"
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
    for (APJECharacterShadowA* Character : SpawnedShadowAArr)
    {
        if (Character)
        {
            Character->SetShadowGeneratorsCount(ShadowGenerators.Num());
        }
    }
}

void UPJEShadowGeneratorManager::AddSpawnedMonster(APJECharacterShadow* SpawnedMonster)
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

void UPJEShadowGeneratorManager::RemoveSpawnedMonster(APJECharacterShadow* SpawnedMonsterToRemove)
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

int32 UPJEShadowGeneratorManager::GetShadowGeneratorsCount() const
{
    return ShadowGenerators.Num();
}

int32 UPJEShadowGeneratorManager::GetShadowACount() const
{
    return SpawnedShadowAArr.Num();
}
