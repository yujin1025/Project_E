// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "DuckProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API ADuckProjectile : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	ADuckProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

	FORCEINLINE void SetItemCode(int32 NewItemCode) { ItemCode = NewItemCode; }

	void SetDamage(float Damage);

protected:
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_GetBall();

public:
	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "item")
	int32 ItemCode;

	float DamageAmount = 0.0f;

private:
	void CalculateGravityScale(float DesiredRange, float InitialSpeed);
};
