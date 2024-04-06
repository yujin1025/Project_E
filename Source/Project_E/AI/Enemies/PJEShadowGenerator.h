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

    virtual void Destroyed() override;

// Spawn Section
public:
    void SpawnMonsterAtRandomLocation();

protected:
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class APJECharacterShadowA> MonsterClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float SpawnRadius = 1000.0f;

};
