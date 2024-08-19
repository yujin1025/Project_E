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

protected:
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_GetBall();


private:
	UPROPERTY(EditAnywhere)
	class USphereComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 3200.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float GravityScale = 4.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "item")
	int32 ItemCode;
};
