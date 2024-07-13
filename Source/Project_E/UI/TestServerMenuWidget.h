// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "TestServerMenuWidget.generated.h"

class UButton;

UCLASS()
class PROJECT_E_API UTestServerMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UTestServerMenuWidget(const FObjectInitializer &ObjectInitializer);
	UFUNCTION(BlueprintCallable, Category = "Widget")
	void MenuSetup(int32 NumberOfPublicConnections = 2, FString TypeOfMatch = FString(TEXT("FreeForAll")));

protected:
	virtual bool Initialize() override;
	virtual void NativeDestruct() override;

	// MultiplayerSessionSubsystem에 있는 Custom Delegate의 Callback함수
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSession(const TArray<FOnlineSessionSearchResult>& SessionResult, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

private:
	TSubclassOf<UUserWidget> LobbyWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;
	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;

	UFUNCTION()
	void PlayButtonClicked();
	UFUNCTION()
	void JoinButtonClicked();
	UFUNCTION()
	void QuitButtonClicked();

	void MenuTearDown();

	class USessionSubsystem* SessionSubsystem;

	int32 NumPublicConnections{2};
	
	FString MatchType{TEXT("FreeForAll")};
};
