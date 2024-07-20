// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALobbyGameMode();

	virtual void Tick(float DeltaSeconds) override;
	
	TArray<APlayerController> PCs;
protected:
	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;
	
	TArray<FString> PlayerNames;
};
