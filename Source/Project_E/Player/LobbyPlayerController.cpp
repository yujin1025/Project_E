// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/LobbyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerState.h"
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

	if(!IsLocalController()) return;
	
	UWorld* World = GetWorld();
	if(World)
	{
		if(GetNetMode() != NM_Standalone)
		{
			LobbyWidget = Cast<ULobbyWidget>(CreateWidget<UUserWidget>(World, LobbyWidgetClass));
			LobbyWidget->AddToViewport();
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
	TArray<FString> PlayerNames;
	for(auto PC : PCs)
	{
		FString PlayerName = PC->PlayerState->GetPlayerName();
		PlayerNames.Add(PlayerName);
	}

	FString Player0Name = PlayerNames[0];
	FString Player1Name = (PlayerNames.Num() < 2) ? FString(TEXT("Waiting...")) : PlayerNames[1];
	
	if(PlayerNames.Num() < 2)
	{
		if(LobbyWidget)
		{
			LobbyWidget->UpdateName(Player0Name, Player1Name);
		}
	}
	else
	{
		Client_UpdateName(Player0Name, Player1Name);
	}
}

void ALobbyPlayerController::Client_UpdateName_Implementation(const FString& Player0Name, const FString& Player1Name)
{
	if(LobbyWidget)
	{
		LobbyWidget->UpdateName(Player0Name, Player1Name);
	}
}