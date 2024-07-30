// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterPlayer.h"
#include "PJECharacterDuck.generated.h"

class UDuckInventoryWidget;
class UAnimMontage;
/**
 *
 */
UCLASS()
class PROJECT_E_API APJECharacterDuck : public APJECharacterPlayer
{
	GENERATED_BODY()

public:
	APJECharacterDuck();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void InitWidget() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RapidFireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;

public:
	void Swallow();

protected:
	void DropItem() override;
	void Fire();
	void ResetFire();
	void RapidFire(const FInputActionValue& Value);
	void SpawnRapidFireProjectile();
	void ResetRapidFire();
	void ApplySpeedReduction();
	void Dash();
	void LogInventory();
	void UpdateInventoryWidget(EItemType ItemType);

	void EnterAimingMode();
	void ExitAimingMode();
	void CalculateProjectilePath();

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
	float DefaultWalkSpeed = 355.0f;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DashMultiplier = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SwallowedMultiplier = 0.7f;

	
	FVector MuzzleLocation;
	FRotator MuzzleRotation;

	// 카메라 위치로부터의 총구 오프셋
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	int32 MagicBallCount;
	FTimerHandle RapidFireTimerHandle;
	int32 RapidFireCount;

	bool bIsAiming;
	bool bIsSwallowed;
	bool bIsInitialized = false;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class ADuckProjectile> ProjectileClass;

	UPROPERTY()
	UDuckInventoryWidget* WeaponInventoryWidget;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UDuckInventoryWidget> WeaponInventoryClass;

	UPROPERTY()
	UDuckInventoryWidget* NonWeaponInventoryWidget;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UDuckInventoryWidget> NonWeaponInventoryClass;

	UItem* SwallowedItem = nullptr;

	/**
	* Animation montages
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* RapidFireMontage;
};