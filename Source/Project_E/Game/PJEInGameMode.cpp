// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEInGameMode.h"

#include "Player/PJEPlayerController.h"

APJEInGameMode::APJEInGameMode()
{
	//SetDefaultPawnClass();
	SetPlayerControllerClass();
	// HUDClass = APJEInGameMode::StaticClass();
	// GameStateClass = APJEInGameMode::StaticClass();
	// PlayerStateClass = APJEInGameMode::StaticClass();
	// SpectatorClass = APJEInGameMode::StaticClass();
}

void APJEInGameMode::SetDefaultPawnClass()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PC/BP_Cat"));
	if(PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void APJEInGameMode::SetPlayerControllerClass()
{
	PlayerControllerClass = APJEPlayerController::StaticClass();
}
