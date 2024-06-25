// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterPlayer.h"
#include "PJECharacterDuck.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_E_API APJECharacterDuck : public APJECharacterPlayer
{
	GENERATED_BODY()

public:
	APJECharacterDuck();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwallowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RapidFireAction;

protected:
	void Grab() override;
	void Swallow();
	void Fire();
	void ResetFire();
	void RapidFire(const FInputActionValue& Value);
	void ResetRapidFire();
	void ResetSpeed();
	void Dash();
	//void ShootProjectile(const FVector& StartLocation, const FVector& LaunchVelocity);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UDataTable* ItemDatabase;

	FTimerHandle ShootDelayTimer;
	FTimerHandle RapidFireDelayTimer;
	bool bCanShoot;
	bool bCanRapidFire;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DashSpeed = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SwallowedSpeed = 0.7;

	bool bIsSwallowed;

	//projectile
private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class APJEProjectile> ProjectileClass;

};