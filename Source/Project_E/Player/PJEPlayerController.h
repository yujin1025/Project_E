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
	
	void SetupInputComponent() override;
	
	void GameOver();

protected:
	void SwitchInputToIgnitionHandle();
	void SwitchInputToPlayer();


};
