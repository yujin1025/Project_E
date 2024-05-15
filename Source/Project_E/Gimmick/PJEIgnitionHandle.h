// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "PJEInputInterface.h"
#include "PJEInteractInterface.h"
#include "GameFramework/Actor.h"
#include "PJEIgnitionHandle.generated.h"

class APJECamPos;
struct FInputActionValue;
class UInputAction;
class UWidgetComponent;
class UBoxComponent;
enum class ERotateState : uint8;
class APJERotatingPlatform;
class APJECharacterPlayer;
class UPJERotationPlatform;

UCLASS()
class PROJECT_E_API APJEIgnitionHandle : public AActor, public IPJEInteractInterface, public IPJEInputInterface
{
	GENERATED_BODY()
	
public:	
	APJEIgnitionHandle();

protected:
	virtual void BeginPlay() override;

	/* Interact Section **/
	virtual void EndInteracting(const AActor* InteractActor) override;
	
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;

	virtual void SetupInputBinding(APJEPlayerController* PlayerController) override;
	/* End Interact Section **/
	
	/** Behavior Section */
	void ReturnPawn();
	void DoRotation(const FInputActionValue& Value);
	void StopRotation();
	/** End Behavior Section */

	void NotifyState(ERotateState RotateState, float Speed);
	
public:	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UWidgetComponent> Widget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBoxComponent> InteractTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TObjectPtr<APJERotatingPlatform>> RotationPlatforms;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	ERotateState CurrentRotateState;
	ERotateState LastRotateState;
	float RotateSpeed = 0;
	
	float TimeAfterInput;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DelayTime;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputMappingContext* HandleContext;
	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* TurnAction;
	UPROPERTY(VisibleAnywhere, Category = "Input")
	UInputAction* InterruptAction;

	UPROPERTY(EditAnywhere, Category = "Camera")
	TObjectPtr<APJECamPos> Campos;
	
	UPROPERTY(VisibleAnywhere, Category = "Input")
	TObjectPtr<APJEPlayerController> CurrentPossessingController;
};
