// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PJEGameState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, int, float)
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	APJEGameState();

	FOnHealthChangedDelegate OnNonPlayerHPChanged;
	
public:
	void OnChangedHealth(int ObjectID, float Amount);
};
