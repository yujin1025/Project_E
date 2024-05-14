// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterPlayer.h"
#include "PJECharacterCat.generated.h"

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

protected:
	virtual void BeginPlay() override;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category = "Jump")
	float JumpHeight = 500.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bFirstJump = true;

	UPROPERTY(EditAnywhere)
	bool bIsWalking = true;

	int32 JumpCount = 0;


	//TEST
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float MovementSpeed;

	virtual void Tick(float DeltaSeconds) override;
	// Action Section
protected:
	void DoubleJump();
	void Dash();
	void StopDash();
	void Attack(); //���
	void Swing();
};