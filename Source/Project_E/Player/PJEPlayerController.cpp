// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

APJEPlayerController::APJEPlayerController()
{
}

void APJEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void APJEPlayerController::GameClear()
{
	//TODO: GameClear
}

void APJEPlayerController::GameOver()
{
	//TODO: GameOver
}


