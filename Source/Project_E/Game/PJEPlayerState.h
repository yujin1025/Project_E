// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PJEPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, float)
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APJEPlayerState();

public:
	FOnHPChangedDelegate OnPlayerHPChanged;

public:
	void OnChangePlayerHealth(int objectId, float Amount);
};
