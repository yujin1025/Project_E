// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PJEShadowGeneratorManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEShadowGeneratorManager : public UObject
{
    GENERATED_BODY()

public:
    static UPJEShadowGeneratorManager* GetInstance();
    void ShutdownInstance();

private:
    static UPJEShadowGeneratorManager* Instance;

// Init Section
public:
    void FindAllShadowGenerators();

// ShadowCount Section
public:
    void RemoveShadowGenerator(class APJEShadowGenerator* GeneratorToRemove);
    void AddShadowGenerator(class APJEShadowGenerator* NewGenerator);

    void AddSpawnedMonster(class APJECharacterShadow* SpawnedMonster);
    void RemoveSpawnedMonster(class APJECharacterShadow* SpawnedMonsterToRemove);

    FORCEINLINE int32 GetShadowGeneratorsCount() const;

protected:
    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<class APJEShadowGenerator>> ShadowGenerators;

    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<class APJECharacterShadowA>> SpawnedShadowAArr;

    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<class APJECharacterShadowB>> SpawnedShadowBArr;

    void UpdateShadowGeneratorsCount();
};
