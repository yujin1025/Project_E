// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LobbyWidget.h"
#include "Interfaces/OnlineFriendsInterface.h"

#include "OnlineSubsystem.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Player/LobbyPlayerController.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

void ULobbyWidget::UpdateName(FString NameOfPlayer0, FString NameOfPlayer1)
{
	if(Player0Name && Player1Name)
	{
		Player0Name->SetText(FText::FromString(NameOfPlayer0));
		Player1Name->SetText(FText::FromString(NameOfPlayer1));	
	}
}

void ULobbyWidget::ChangeRoleImage()
{
	UTexture2D* TmpTexture = Cast<UTexture2D>(Player0Image->Brush.GetResourceObject());
	if(TmpTexture)
	{
		Player0Image->SetBrushFromTexture(Cast<UTexture2D>(Player1Image->Brush.GetResourceObject()));
		Player1Image->SetBrushFromTexture(TmpTexture);
	}
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
		if(GetWorld()->GetNetMode() == NM_Client)
		{
			StartButton->SetIsEnabled(false);
		}
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

void ULobbyWidget::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}


void ULobbyWidget::OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName,
                                             const FString& ErrorStr)
{
	if(!bWasSuccessful) return;
}

void ULobbyWidget::ChangeButtonClicked()
{
	UWorld* World = GetWorld();
	if(World)
	{
		ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(World->GetFirstPlayerController());
		LobbyPC->Server_ChangeButtonClicked();
	}
}

void ULobbyWidget::StartButtonClicked()
{
	UWorld* World = GetWorld();
	if(World)
	{
		ALobbyPlayerController* LobbyPC = Cast<ALobbyPlayerController>(World->GetFirstPlayerController());
		LobbyPC->Server_StartButtonClicked();
	}
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

void ULobbyWidget::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}

