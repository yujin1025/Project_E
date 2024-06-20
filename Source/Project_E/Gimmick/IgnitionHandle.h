// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "IgnitionHandle.generated.h"

enum class ERotateState : uint8;

UCLASS()
class PROJECT_E_API AIgnitionHandle : public APJEInteractiveActor 
{
	GENERATED_BODY()
	
public:	
	AIgnitionHandle();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	void NotifyPlatform(ERotateState RotateState, float RotateSpeed);

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	TArray<class APJERotatingPlatform*> RotatingPlatforms;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputMappingContext* HandleContext;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	class UInputAction* TurnAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* InterruptAction;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class APJECamPos* Campos;
	
	ERotateState CurrentRotateState;
	ERotateState LastRotateState;
	float RotateSpeed = 0.f;
	float TimeAfterInput = 0.f;
	float DelayTime = 2.f;
	
};
