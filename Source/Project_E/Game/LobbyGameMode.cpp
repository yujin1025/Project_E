// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameSession/LobbySession.h"
#include "Player/LobbyPlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{
	GameSessionClass = ALobbySession::StaticClass();

	PlayerControllerClass = ALobbyPlayerController::StaticClass();

	PlayerStateClass = APJEPlayerState::StaticClass();
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	LobbySession = Cast<ALobbySession>(GameSession);
	if(LobbySession)
	{
		LobbySession->AddPC(GetWorld()->GetFirstPlayerController());
	}
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{	
	Super::PostLogin(NewPlayer);
	
	if(LobbySession)
	{
		LobbySession->RegisterPlayer(NewPlayer, NewPlayer->PlayerState->GetUniqueId().GetUniqueNetId(), false);
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if(LobbySession)
	{
		LobbySession->UnregisterPlayer(Cast<APlayerController>(Exiting));
	}
}

