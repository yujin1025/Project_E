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


    UFUNCTION(Server, Reliable, WithValidation)
    void Server_SpawnMonster(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation, bool bAddToManager = true);
    bool Server_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation, bool bAddToManager = true);
    void Server_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation, bool bAddToManager = true);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SpawnMonster(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager);
    bool Multicast_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager);
    void Multicast_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& SpawnLocation, bool bAddToManager);

protected:
    FTimerHandle SpawnTimerHandle;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class APJECharacterShadowA> ShadowAClass;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<class APJECharacterShadowB> ShadowBClass;

    void StartSpawnTimer();
    void SpawnShadowAWithTimer();


    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};