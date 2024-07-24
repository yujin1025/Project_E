// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LobbyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "GameSession/LobbySession.h"
#include "UI/LobbyWidget.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyWidgetAsset(TEXT("UserWidget '/Game/UI/WBP_Lobby.WBP_Lobby_C'"));
	if(LobbyWidgetAsset.Succeeded())
	{
		LobbyWidgetClass = LobbyWidgetAsset.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		UWorld* World = GetWorld();
		if(World)
		{
			if(GetNetMode() != NM_Standalone)
			{
				LobbyWidget = Cast<ULobbyWidget>(CreateWidget<UUserWidget>(World, LobbyWidgetClass));
				LobbyWidget->AddToViewport();
			}
		}
		Server_InitSetting();
	}
}

void ALobbyPlayerController::Server_InitSetting_Implementation()
{
	// Player Role Setting
	UWorld* World = GetWorld();
	if(World && World->GetAuthGameMode())
	{
		ALobbySession* LobbySession = Cast<ALobbySession>(World->GetAuthGameMode()->GameSession);
		if(LobbySession)
		{
			TArray<EPlayerRole> PlayerRoles = LobbySession->GetPlayerRoles();
			if(PlayerRoles[0] == EPlayerRole::Duck)
			{
				Client_ChangeRoleImage();
			}
		}
	}
}

void ALobbyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsLocalController())
	{
		ENetMode NetMode = GetNetMode();
		switch (NetMode)
		{
		case NM_Standalone:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : Standalone")));
			break;
		case NM_ListenServer:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : ListenServer")));
			break;
		case NM_Client:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : Client")));
			break;
		}
	}
}

void ALobbyPlayerController::UpdateWidget(TArray<APlayerController*> PCs)
{
	UpdateName(PCs);
}

void ALobbyPlayerController::UpdateName(TArray<APlayerController*> PCs)
{
	TArray<FString> PlayerNames;
	for(auto PC : PCs)
	{
		FString PlayerName = PC->PlayerState->GetPlayerName();
		PlayerNames.Add(PlayerName);
	}

	FString Player0Name = PlayerNames[0];
	FString Player1Name = (PlayerNames.Num() < 2) ? FString(TEXT("Waiting...")) : PlayerNames[1];
	
	Client_UpdateName(Player0Name, Player1Name);
}

void ALobbyPlayerController::Client_UpdateName_Implementation(const FString& Player0Name, const FString& Player1Name)
{
	if(LobbyWidget)
	{
		LobbyWidget->UpdateName(Player0Name, Player1Name);
	}
}

void ALobbyPlayerController::Server_ChangeButtonClicked_Implementation()
{
	UWorld* World = GetWorld();
	if(World && World->GetAuthGameMode())
	{
		ALobbySession* LobbySession = Cast<ALobbySession>(World->GetAuthGameMode()->GameSession);
		if(LobbySession)
		{
			LobbySession->ChangeRole();
		}
	}
}

void ALobbyPlayerController::Server_StartButtonClicked_Implementation()
{
	UWorld* World = GetWorld();
	if(World && World->GetAuthGameMode())
	{
		ALobbySession* LobbySession = Cast<ALobbySession>(World->GetAuthGameMode()->GameSession);
		if(LobbySession)
		{
			LobbySession->GameStart();
		}
	}
}


void ALobbyPlayerController::GameStart()
{
	Client_GameStart();
}

void ALobbyPlayerController::Client_GameStart_Implementation()
{
	LobbyWidget->MenuTearDown();
	LobbyWidget = nullptr;
	
	if(GetNetMode() == NM_ListenServer)
	{
		UWorld* World = GetWorld();
		if(World)
		{
			World->GetAuthGameMode()->bUseSeamlessTravel = true;
			World->ServerTravel("/Game/Maps/MinjiTestMap?listen");
		}
	}
}

void ALobbyPlayerController::ChangeRoleImage()
{
	Client_ChangeRoleImage();
}


void ALobbyPlayerController::Client_ChangeRoleImage_Implementation()
{
	if(LobbyWidget)
	{
		LobbyWidget->ChangeRoleImage();
	}
}
