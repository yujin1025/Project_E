// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"


class ULobbyWidget;

UCLASS()
class PROJECT_E_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void UpdateWidget(TArray<APlayerController*> PCs);

	UFUNCTION(Client, Reliable)
	void Client_UpdateName(const FString& Player0Name, const FString& Player1Name);

private:
	TSubclassOf<UUserWidget> LobbyWidgetClass;
	ULobbyWidget* LobbyWidget;
};
