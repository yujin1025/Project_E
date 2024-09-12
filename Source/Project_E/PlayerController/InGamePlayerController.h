// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UENUM(BlueprintType)
enum class EInputType : uint8
{
	IT_Player,
	IT_Handle,
	IT_Cylinder,
};


UCLASS()
class PROJECT_E_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void Client_SwitchInput(EInputType InputType);
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	// Player Function
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump();
	void Dash(const bool bIsDash);
	void Drop();
	void Interact();
	void Shoot();
	void Aim();
	
	// Handle Function
	
	
	// Cylinder Function
	
	
private:
	// Player Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputMappingContext* PlayerContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* DashAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* DropAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* InteractAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|PlayerInput")
	UInputAction* AimAction;
	
	// Handle Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|HandleInput")
	UInputMappingContext* HandleContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|HandleInput")
	UInputAction* TurnAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input|HandleInput")
	UInputAction* InterruptAction;

	//Cylinder Context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputMappingContext* CylinderContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputAction* PushAction;
};
