// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEShokeWave.generated.h"

UCLASS()
class PROJECT_E_API APJEShockwave : public AActor
{
    GENERATED_BODY()

public:
    APJEShockwave();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class USphereComponent> InnerCollisionSphere;

    UPROPERTY(EditAnywhere, Category = "Damage")
    float DamagePerSec;

    float Radius;

    float InnerRadius;

    UPROPERTY(EditAnywhere, Category = "Collider")
    float ExpandSpeed;

    UPROPERTY(EditAnywhere, Category = "Duration")
    float ShokeWaveDuration;

    float TimeElapsed;

    void DrawDebugSpheres();

    UPROPERTY()
    TSet<TObjectPtr<class APJECharacterPlayer>> OverlappingActors;

    UPROPERTY()
    TSet<TObjectPtr<class APJECharacterPlayer>> InnerOverlappingActors;

    void ExpandShokeWave(float DeltaTime);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    UFUNCTION()
    void OnInnerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    UFUNCTION()
    void OnInnerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
