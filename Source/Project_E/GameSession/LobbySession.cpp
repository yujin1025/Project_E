// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSession/LobbySession.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Player/LobbyPlayerController.h"


ALobbySession::ALobbySession()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.4f;
}

void ALobbySession::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for(auto PC : PCs)
	{
		ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(PC);
		LobbyPC->UpdateWidget(PCs);
	}
}

void ALobbySession::ChangeRole()
{
	EPlayerRole TmpRole = PlayerRoles[0];
	PlayerRoles[0] = PlayerRoles[1];
	PlayerRoles[1] = TmpRole;

	for(auto PC : PCs)
	{
		ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(PC);
		LobbyPC->ChangeRoleImage();
	}
}

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
}

void ALobbySession::UnregisterPlayer(const APlayerController* ExitingPlayer)
{
	Super::UnregisterPlayer(ExitingPlayer);

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			for(auto PC : PCs)
			{
				if(PC == ExitingPlayer)
				{
					PCs.Remove(PC);
				}
			}

			UnregisterPlayerDelegateHandle =
				Session->AddOnUnregisterPlayersCompleteDelegate_Handle(
					FOnUnregisterPlayersCompleteDelegate::CreateUObject(this, &ThisClass::OnUnregisterPlayerComplete));
		}
	}
}

void ALobbySession::OnUnregisterPlayerComplete(FName NameOfSession, const TArray<FUniqueNetIdRef>& PlayerIds,
                                               bool bWasSuccessful)
{

	if(!bWasSuccessful) return;

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Success to UnRegister Player!")));
		}
	}
}
