// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSession/LobbySession.h"

#include "OnlineSubsystem.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineSessionInterface.h"


ALobbySession::ALobbySession()
{
	
}

void ALobbySession::BeginPlay()
{
	Super::BeginPlay();
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
			
			for(auto PC : PCs)
			{
				FString PCName = PC->GetName();
				if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("PC's Name : %s"), *PCName));
			}
		}
	}

	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("PC's Num : %d"), PCs.Num()));

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

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr Session = OnlineSubsystem->GetSessionInterface();
		if(Session.IsValid())
		{
			// PC에서 ExitingPlayer 제거
			// UnRegisterDelegateHandle 생성
			//
			for(auto PC : PCs)
			{
				if(PC == ExitingPlayer)
				{
					// 해당하는 PC를 PCs에서 제거
					PCs.Remove(PC);
				}
			}

			UnregisterPlayerDelegateHandle =
				Session->AddOnUnregisterPlayersCompleteDelegate_Handle(
					FOnUnregisterPlayersCompleteDelegate::CreateUObject(this, &ThisClass::OnUnregisterPlayerComplete));
		}
	}
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("PC's Num : %d"), PCs.Num()));
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
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Success to UnRegister Player!")));
		}
	}
}
