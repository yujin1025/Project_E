// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterPlayer.h"
#include "PJECharacterDuck.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterDuck : public APJECharacterPlayer
{
	GENERATED_BODY()
public:
	APJECharacterDuck();

protected:
	virtual void BeginPlay() override;

// TODO : Attack, Shoot, Swallow, etc...
};
