// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <Player/PJEPlayerController.h>
#include "PJEPlayerState.h"
#include "PJEGameState.h"

APJEGameModeBase::APJEGameModeBase()
{
	CharacterStatTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/CharacterStat"));
	PlayerControllerClass = APJEPlayerController::StaticClass();
	PlayerStateClass = APJEPlayerState::StaticClass();
	GameStateClass = APJEGameState::StaticClass();
}

void APJEGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void APJEGameModeBase::OnPlayerDead(int PlayerNumber)
{
	APJEPlayerController* PlayerController = Cast<APJEPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerNumber));
	if (PlayerController)
	{
		PlayerController->GameOver();
	}
}


void APJEGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Emerald, FString::Printf(TEXT("1")));
	MyGameState = Cast<APJEGameState>(GameState);
}

void APJEGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Emerald, FString::Printf(TEXT("2")));
	OnPostLogin(Cast<APJEPlayerController>(NewPlayer));
}

void APJEGameModeBase::OnPostLogin(APJEPlayerController* NewPlayer)
{
	if(NewPlayer)
		MyPlayerState = NewPlayer->GetState();
}

FCharacterStatData* APJEGameModeBase::GetCharacterStat(ECharacterType type)
{
	int IntType = (int)type;
	FName StringType = *FString::FromInt(IntType);

	return CharacterStatTable->FindRow<FCharacterStatData>(StringType, TEXT(""));
}
