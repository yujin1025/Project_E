// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PJEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APJEPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void GameOver();
	void SwitchInputToOther();
	void SwitchInputToPawn();

	FORCEINLINE APawn* GetPlayerPawn() {return PlayerPawn;}
	
protected:
	TObjectPtr<APawn> PlayerPawn = NULL;
	TObjectPtr<AActor> LastBindingActor = NULL;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> CurrentBindingActor = NULL;
	
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
};
