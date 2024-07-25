// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/PJEGameModeBase.h"
#include "PJEInGameMode.generated.h"

class APJECharacterPlayer;
class APJECharacterDuck;
class APJECharacterCat;
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEInGameMode : public APJEGameModeBase
{
	GENERATED_BODY()

public:
	APJEInGameMode();
	
protected:
	virtual void BeginPlay() override;
	
	void SetPlayerControllerClass();

	void InitializePlayer();
	
	virtual void PostSeamlessTravel() override;

private:
	TSubclassOf<APJECharacterPlayer> PlayerClass;

	TSubclassOf<APJECharacterCat> CatClass;
	TSubclassOf<APJECharacterDuck> DuckClass;

	FTransform GameStartTransform;
};
