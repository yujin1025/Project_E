// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEShokeWave.generated.h"

UCLASS()
class PROJECT_E_API APJEShokeWave : public AActor
{
    GENERATED_BODY()

public:
    APJEShokeWave();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(EditAnywhere, Category = "Damage")
    float DamageAmount;

    // 저장된 겹쳐진 액터
    UPROPERTY()
    TArray<TObjectPtr<AActor>> OverlappingActors;

    void ExpandShokeWave(float DeltaTime);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
