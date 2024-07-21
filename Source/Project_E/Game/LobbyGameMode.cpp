// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameSession/LobbySession.h"

ALobbyGameMode::ALobbyGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GameSessionClass = ALobbySession::StaticClass();
}

void ALobbyGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{	
	Super::PostLogin(NewPlayer);
	
	ALobbySession* LobbySession = Cast<ALobbySession>(GameSession);
	if(LobbySession)
	{
		LobbySession->RegisterPlayer(NewPlayer, NewPlayer->PlayerState->GetUniqueId().GetUniqueNetId(), false);
	}
	
	APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	if(PlayerState)
	{
		FString PlayerName = PlayerState->GetPlayerName();
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Yellow, FString::Printf(TEXT("%s has joined the server"), *PlayerName));
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	ALobbySession* LobbySession = Cast<ALobbySession>(GameSession);
	if(LobbySession)
	{
		LobbySession->UnregisterPlayer(Cast<APlayerController>(Exiting));
	}
}

