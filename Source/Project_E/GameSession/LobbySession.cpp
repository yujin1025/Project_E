// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSession/LobbySession.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void ALobbySession::RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdPtr& UniqueId, bool bWasFromInvite)
{
	Super::RegisterPlayer(NewPlayer, UniqueId, bWasFromInvite);

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			PCs.Add(NewPlayer);

			RegisterPlayerDelegateHandle =
				Session->AddOnRegisterPlayersCompleteDelegate_Handle(
					FOnRegisterPlayersCompleteDelegate::CreateUObject(this, &ThisClass::OnRegisterPlayerComplete));

			if(!Session->RegisterPlayer(SessionName, *UniqueId, false))
			{
				Session->ClearOnRegisterPlayersCompleteDelegate_Handle(
					RegisterPlayerDelegateHandle);
				RegisterPlayerDelegateHandle.Reset();
			}
		}
	}
}

void ALobbySession::OnRegisterPlayerComplete(FName NameOfSession, const TArray<FUniqueNetIdRef>& PlayerIds,
	bool bWasSuccessful)
{
	if(!bWasSuccessful) return;
	
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Success to Register Player!")));
		}
	}
}

void ALobbySession::UnregisterPlayer(const APlayerController* ExitingPlayer)
{
	Super::UnregisterPlayer(ExitingPlayer);
}


void ALobbySession::OnUnregisterPlayerComplete(FName NameOfSession, const TArray<FUniqueNetIdRef>& PlayerIds,
	bool bWasSuccessful)
{
	
}
