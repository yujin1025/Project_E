// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEInGameMode.h"

#include "PJEPlayerState.h"
#include "Player/PJEPlayerController.h"

APJEInGameMode::APJEInGameMode()
{
	SetPlayerControllerClass();

	bUseSeamlessTravel = true;
}

void APJEInGameMode::SetPlayerControllerClass()
{
	PlayerControllerClass = APJEPlayerController::StaticClass();
}

void APJEInGameMode::InitializePlayer()
{
	
}

void APJEInGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	if(GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Emerald, FString::Printf(TEXT("Seamless Travel Complete")));
}

