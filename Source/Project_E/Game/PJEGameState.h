// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PJEGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APJEGameState();
	
public:
	void OnChangedHealth(int ObjectID, float Amount);
};
