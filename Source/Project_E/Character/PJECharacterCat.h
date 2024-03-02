// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterPlayer.h"
#include "PJECharacterCat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterCat : public APJECharacterPlayer
{
	GENERATED_BODY()
	
public:
	APJECharacterCat();

protected:
	virtual void BeginPlay() override;

// Action Section
protected:
	//TODO : Attack, Jump, Swing, etc...
};
