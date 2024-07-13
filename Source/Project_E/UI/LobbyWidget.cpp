// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyWidget.h"
#include "Interfaces/OnlineFriendsInterface.h"

#include "OnlineSubsystem.h"
#include "Components/Button.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

bool ULobbyWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}
	
	if(ChangeButton)
	{
		ChangeButton->OnClicked.AddDynamic(this, &ThisClass::ChangeButtonClicked);
	}
	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ThisClass::StartButtonClicked);
	}
	if(MainButton)
	{
		MainButton->OnClicked.AddDynamic(this, &ThisClass::MainButtonClicked);
	}

	// Get Steam FriendList
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineFriendsPtr Friends = OnlineSubsystem->GetFriendsInterface();
		if(Friends)
		{
			Friends->ReadFriendsList(0, TEXT(""), FOnReadFriendsListComplete::CreateUObject(this, &ThisClass::OnReadFriendsListComplete));
		}
	}
	
	return true;
}


void ULobbyWidget::OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
	const FString& ErrorStr)
{
	if(!bWasSuccessful) return;
}


void ULobbyWidget::ChangeButtonClicked()
{
}

void ULobbyWidget::StartButtonClicked()
{
}

void ULobbyWidget::MainButtonClicked()
{
}
