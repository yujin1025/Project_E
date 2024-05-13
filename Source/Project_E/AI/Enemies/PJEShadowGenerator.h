// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEShadowGenerator.generated.h"

UCLASS()
class PROJECT_E_API APJEShadowGenerator : public AActor
{
    GENERATED_BODY()

public:
    APJEShadowGenerator();
    virtual void BeginPlay() override;
    virtual void Destroyed() override;

// Mesh Section
protected:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CubeMesh;

// Spawn Section
public:
    template <typename ShadowType>
    void SpawnMonsterAtRandomLocation(TSubclassOf<ShadowType> MonsterClass, bool bAddToManager = true);

protected:
    FTimerHandle SpawnTimerHandle;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class APJECharacterShadowA> ShadowAClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class APJECharacterShadowB> ShadowBClass;

    void StartSpawnTimer();
    void SpawnShadowAWithTimer();
};
