// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PJEPlayerController.generated.h"

UENUM(BlueprintType)
enum class EControllerOperation : uint8
{
	ECO_Pawn UMETA(DisplayName = "플레이어 조작"),
	ECO_IgnitionHandle UMETA(DisplayName = "점화손잡이 조작"),
	ECO_Push UMETA(DisplayName = "밀기 조작"),
	ECO_Roll UMETA(DisplayName = "굴리기 조작"),
};

UCLASS()
class PROJECT_E_API APJEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APJEPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Switch Input Function
	void InitInputPawn();
	void InitInputIgnitionHandle();
	void InitInputPush();
	void InitInputRoll();

	void GameOver();

	FORCEINLINE APawn* GetPlayerPawn() {return PlayerPawn;}
	
protected:
	TObjectPtr<APawn> PlayerPawn = NULL;
	TObjectPtr<AActor> OperatingActor = NULL;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IgnitionHandleContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* CylinderContext;

	UPROPERTY(VisibleAnywhere)
	EControllerOperation ControllerOperation = EControllerOperation::ECO_Pawn;

public:
	FORCEINLINE void SetOperatingActor(AActor* OpActor) { OperatingActor = OpActor; }
};
