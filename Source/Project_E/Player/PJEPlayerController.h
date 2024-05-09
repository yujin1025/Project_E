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
	
	void GameOver();
	void SwitchInputToIgnitionHandle();
	void SwitchInputToPlayer();
	void SetPlayerStart();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<APawn> PlayableCharacterClass;

	APawn* PlayerPawn;
	
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
};
