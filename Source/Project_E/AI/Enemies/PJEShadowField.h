// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEShadowField.generated.h"

UCLASS()
class PROJECT_E_API APJEShadowField : public AActor
{
    GENERATED_BODY()

public:
    APJEShadowField();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void InitializeField(float Duration, float Damage, float InitialRadius);

    UFUNCTION()
    void DestroySelf(AActor* DestroyedActor);

private:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<class USphereComponent> CollisionSphere;

    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UStaticMeshComponent> FieldMesh;

    UPROPERTY()
    TObjectPtr<class UBehaviorTreeComponent> CachedOwnerComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<class UNiagaraComponent> NiagaraComponent;

    float FieldDuration;
    float DamagePerSecond;
    float TimeElapsed;
    float FieldRadius;

    // 저장된 겹쳐진 액터
    UPROPERTY()
    TArray<TObjectPtr<AActor>> OverlappingActors;

    void ShrinkField(float DeltaTime);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};