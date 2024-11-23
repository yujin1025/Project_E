// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterPlayer.h"
#include "PJECharacterCat.generated.h"

class UCatInventoryWidget;
class UAnimMontage;
/**
 *
 */
UCLASS()
class PROJECT_E_API APJECharacterCat : public APJECharacterPlayer
{
	GENERATED_BODY()

public:
	APJECharacterCat();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void InitWidget() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Data")
	class UDataTable* ItemDatabase;

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	UInventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwingAction;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DashSpeed = 1.5f;

public:
	bool Grab();

	virtual ACatWeapon* GetEquippedWeapon() const override;

protected:
	void DoubleJump() override;
	void JumpAttacking();
	virtual void Landed(const FHitResult& Hit) override;
	void Swing();
	void Dash();
	void DropItem() override;

private:
	UPROPERTY()
	UCatInventoryWidget* CatInventoryWidget;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UCatInventoryWidget> CatInventoryClass;

	UPROPERTY()
	ACatWeapon* EquippedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SwingMontage;

	bool bIsJumping = false;

public:
	// Multiplay Section
	UFUNCTION(Server, Reliable)
	void Server_DoubleJumpAttack();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Grab();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateInventory(int32 ItemID);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_GrabWeapon(ACatWeapon* Weapon);

	UFUNCTION(Server, Reliable)
	void Server_DropItem();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DropInventory(UItem* Item);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Swing();

	UFUNCTION(Server, Reliable)
	void Server_Swing();
};