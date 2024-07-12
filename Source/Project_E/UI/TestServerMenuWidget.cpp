// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TestServerMenuWidget.h"

void UTestServerMenuWidget::MenuSetup(int32 NumberOfPublicConnections, FString TypeOfMatch, FString LobbyPath)
{
}

bool UTestServerMenuWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	return true;
}

void UTestServerMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UTestServerMenuWidget::OnCreateSession(bool bWasSuccessful)
{
}

void UTestServerMenuWidget::OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionSearchResults,
	bool bWasSuccessful)
{
}

void UTestServerMenuWidget::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
}

void UTestServerMenuWidget::OnDestroySession(bool bWasSuccessful)
{
}

void UTestServerMenuWidget::OnStartSession(bool bWasSuccessful)
{
}

void UTestServerMenuWidget::MenuTearDown()
{
}
