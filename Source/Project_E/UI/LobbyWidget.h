// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;

UCLASS()
class PROJECT_E_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ULobbyWidget(const FObjectInitializer &ObjectInitializer);

	void UpdateName(FString NameOfPlayer0, FString NameOfPlayer1);

	void ChangeRoleImage();

protected:
	virtual bool Initialize() override;

	UFUNCTION()
	void ChangeButtonClicked();
	UFUNCTION()
	void StartButtonClicked();
	UFUNCTION()
	void MainButtonClicked();

	void OnReadFriendsListComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);
	
private:
	TSubclassOf<UUserWidget> FriendRowWidgetClass;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ChangeButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* MainButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Player0Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Player1Name;

	UPROPERTY(meta = (BindWidget))
	UImage* Player0Image;
	UPROPERTY(meta = (BindWidget))
	UImage* Player1Image;
	

	class USessionSubsystem* SessionSubsystem;
};
