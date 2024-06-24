// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "IgnitionHandle.generated.h"

struct FInputActionValue;
enum class ERotateState : uint8;

UCLASS()
class PROJECT_E_API AIgnitionHandle : public APJEInteractiveActor 
{
	GENERATED_BODY()
	
public:	
	AIgnitionHandle();
	virtual void Tick(float DeltaTime) override;
	void InitInput(UEnhancedInputComponent* EnhancedInputComponent);
	
protected:
	virtual void BeginPlay() override;
	
	void ReturnPawn();

	UFUNCTION(Client, Reliable)
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;
	
	void NotifyPlatform(ERotateState RotateState, float RotateSpeed);

	void DoRotation(const FInputActionValue& Value);
	void StopRotation();
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	TArray<class APJERotatingPlatform*> RotatingPlatforms;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = true))
	class UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = true))
	UInputAction* InterruptAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = true))
	class APJECamPos* Campos;
	
	ERotateState CurrentRotateState;
	ERotateState LastRotateState;
	float RotateSpeed = 0.f;
	float TimeAfterInput = 0.f;
	float DelayTime = 2.f;

	FVector SavedLocation;
	FRotator SavedRotation;
	
};
