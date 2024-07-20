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
	
	ENetMode CurrentNetMode = GetNetMode();
	if(CurrentNetMode == NM_Standalone)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, FString::Printf(TEXT("Standalone : %f"), DeltaSeconds));
	}
	else if(CurrentNetMode == NM_ListenServer)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, FString::Printf(TEXT("ListenServer")));
	}
	else if(CurrentNetMode == NM_Client)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Yellow, FString::Printf(TEXT("Client : %f"), DeltaSeconds));
	}
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
	if(PlayerState)
	{
		FString PlayerName = PlayerState->GetPlayerName();
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Yellow, FString::Printf(TEXT("%s has joined the server"), *PlayerName));
	}
	
}
