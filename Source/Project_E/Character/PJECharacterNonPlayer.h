// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterBase.h"
#include "Interface/PJECharacterAIInterface.h"
#include "PJECharacterNonPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterNonPlayer : public APJECharacterBase
{
	GENERATED_BODY()
public:
	APJECharacterNonPlayer();

protected:
	virtual void PostInitializeComponents() override;
protected:
	virtual void BeginPlay() override;
protected:
	void SetDead() override;
};
