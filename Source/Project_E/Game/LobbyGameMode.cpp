// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LobbyGameMode.h"

#include "GameSession/LobbySession.h"

ALobbyGameMode::ALobbyGameMode()
{
	GameSessionClass = ALobbySession::StaticClass();
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}
