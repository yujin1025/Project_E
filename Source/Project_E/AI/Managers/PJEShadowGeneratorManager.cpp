// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "AI/Enemies/PJEShadowGenerator.h"
#include "Character/PJECharacterShadowA.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"


TObjectPtr<UPJEShadowGeneratorManager> UPJEShadowGeneratorManager::Instance = nullptr;

UPJEShadowGeneratorManager* UPJEShadowGeneratorManager::GetInstance()
{
    if (!Instance)
    {
        Instance = NewObject<UPJEShadowGeneratorManager>();
    }
    return Instance;
}

void UPJEShadowGeneratorManager::FindAllShadowGenerators()
{
    ShadowGenerators.Empty();

    if (GEngine)
    {
        UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
        if (World)
        {
            for (TActorIterator<APJEShadowGenerator> It(World); It; ++It)
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
    ShadowGenerators.RemoveSingle(GeneratorToRemove);
    UpdateShadowGeneratorsCount();
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
