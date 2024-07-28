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
    static void ShutdownInstance();

private:
    static UPJEShadowGeneratorManager* Instance;

    // Init Section
public:
    void FindAllShadowGenerators();

    // ShadowCount Section
public:
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_RemoveShadowGenerator(class APJEShadowGenerator* GeneratorToRemove);

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_AddShadowGenerator(class APJEShadowGenerator* NewGenerator);

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_AddSpawnedMonster(class APJECharacterShadow* SpawnedMonster);

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_RemoveSpawnedMonster(class APJECharacterShadow* SpawnedMonsterToRemove);

    FORCEINLINE int32 GetShadowGeneratorsCount() const;
    FORCEINLINE int32 GetShadowACount() const;

protected:
    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_ShadowGenerators)
    TArray<TObjectPtr<class APJEShadowGenerator>> ShadowGenerators;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpawnedShadowAArr)
    TArray<TObjectPtr<class APJECharacterShadowA>> SpawnedShadowAArr;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_SpawnedShadowBArr)
    TArray<TObjectPtr<class APJECharacterShadowB>> SpawnedShadowBArr;

    UFUNCTION()
    void OnRep_ShadowGenerators();

    UFUNCTION()
    void OnRep_SpawnedShadowAArr();

    UFUNCTION()
    void OnRep_SpawnedShadowBArr();

    void UpdateShadowGeneratorsCount();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
