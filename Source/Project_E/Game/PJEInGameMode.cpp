// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEInGameMode.h"

#include "PJEPlayerState.h"
#include "Player/PJEPlayerController.h"

APJEInGameMode::APJEInGameMode()
{
	SetPlayerControllerClass();
}

void APJEInGameMode::SetPlayerControllerClass()
{
	PlayerControllerClass = APJEPlayerController::StaticClass();
}

void APJEInGameMode::InitializePlayer()
{
	
}

