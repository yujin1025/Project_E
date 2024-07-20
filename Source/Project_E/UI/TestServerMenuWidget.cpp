// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TestServerMenuWidget.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "Components/SplineComponent.h"
#include "GameSession/SessionSubsystem.h"
#include "Kismet/GameplayStatics.h"

UTestServerMenuWidget::UTestServerMenuWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> LobbyWidgetAsset(TEXT("UserWidget '/Game/UI/WBP_Lobby.WBP_Lobby_C'"));
	if(LobbyWidgetAsset.Succeeded())
	{
		LobbyWidgetClass = LobbyWidgetAsset.Class;
	}
}

void UTestServerMenuWidget::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch)
{
	NumPublicConnections = NumberOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		SessionSubsystem = GameInstance->GetSubsystem<USessionSubsystem>();
		if(SessionSubsystem)
		{
			SessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
			SessionSubsystem->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::OnFindSession);
			SessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);
			SessionSubsystem->MultiplayerOnDestroySessionComplete.AddDynamic(this, &ThisClass::OnDestroySession);
		}
	}
}

bool UTestServerMenuWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	if(PlayButton)
	{
		PlayButton->OnClicked.AddDynamic(this, &ThisClass::PlayButtonClicked);
	}
	if(JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}
	if(QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &ThisClass::QuitButtonClicked);
	}
	
	return true;
}

void UTestServerMenuWidget::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void UTestServerMenuWidget::OnCreateSession(bool bWasSuccessful)
{
	if(bWasSuccessful)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Success to create session")));
		MenuTearDown();
		
		UWorld* World = GetWorld();
		if(World)
		{
			FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(World);
			World->ServerTravel(CurrentLevelName + TEXT("?listen"));
		}
	}
	else
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Failed to create session")));
	}
}

void UTestServerMenuWidget::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful)
{
	if(!SessionSubsystem) return;

	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Session Num : %d"), SessionResult.Num()));
	
	for(auto Result : SessionResult)
	{
		FString SettingValue;
		Result.Session.SessionSettings.Get(FName("MatchType"), SettingValue);
		if(SettingValue == MatchType)
		{
			SessionSubsystem->JoinSession(Result);
			return;
		}
	}

	if(!bWasSuccessful || SessionResult.Num() == 0)
	{
		JoinButton->SetIsEnabled(true);
	}
}

void UTestServerMenuWidget::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if(OnlineSubsystem)
	{
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			FString Address;
			SessionInterface->GetResolvedConnectString(NAME_GameSession ,Address);

			APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
			if(PlayerController)
			{
				if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Address : %s"), *Address));
				PlayerController->ClientTravel(Address, TRAVEL_Absolute);
			}
		}
	}

	if(Result != EOnJoinSessionCompleteResult::Success)
	{
		JoinButton->SetIsEnabled(true);
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 600.f, FColor::Yellow, FString::Printf(TEXT("Failed to join session")));
	}
}

void UTestServerMenuWidget::OnDestroySession(bool bWasSuccessful)
{
}

void UTestServerMenuWidget::PlayButtonClicked()
{
	PlayButton->SetIsEnabled(false);

	if(SessionSubsystem)
	{
		SessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UTestServerMenuWidget::JoinButtonClicked()
{
	JoinButton->SetIsEnabled(false);

	if(SessionSubsystem)
	{
		SessionSubsystem->FindSession(100);
	}
}

void UTestServerMenuWidget::QuitButtonClicked()
{
}

void UTestServerMenuWidget::MenuTearDown()
{
	RemoveFromParent();
}
