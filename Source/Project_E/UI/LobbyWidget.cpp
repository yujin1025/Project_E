// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyWidget.h"
#include "Interfaces/OnlineFriendsInterface.h"

#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameSession/SessionSubsystem.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void ULobbyWidget::UpdateName(FString NameOfPlayer0, FString NameOfPlayer1)
{
	Player0Name->SetText(FText::FromString(NameOfPlayer0));
	Player1Name->SetText(FText::FromString(NameOfPlayer1));
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

	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		SessionSubsystem = GameInstance->GetSubsystem<USessionSubsystem>();
		if(SessionSubsystem)
		{
			SessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
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
	MainButton->SetIsEnabled(false);

	APlayerController* PlayerController = GetOwningPlayer();
	if(PlayerController)
	{
		PlayerController->ClientTravel("/Game/ThirdPerson/Maps/ThirdPersonMap", TRAVEL_Absolute);
	}
}

void ULobbyWidget::OnDestroySession(bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Success to destroy session")));
	}
	else
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Failed to destroy session")));
	}
}
