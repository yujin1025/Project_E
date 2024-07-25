// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEInGameMode.h"

#include "EngineUtils.h"
#include "PJEPlayerState.h"
#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"
#include "GameFramework/PlayerStart.h"
#include "Player/PJEPlayerController.h"
#include "Player/PJEPlayerStart.h"

APJEInGameMode::APJEInGameMode()
{
	SetPlayerControllerClass();
	
	static ConstructorHelpers::FClassFinder<APawn> CatBPClass(TEXT("/Game/Blueprints/PC/BP_Cat"));
	static ConstructorHelpers::FClassFinder<APawn> DuckBPClass(TEXT("/Game/Blueprints/PC/BP_Duck"));
	if(CatBPClass.Class && DuckBPClass.Class)
	{
		CatClass = CatBPClass.Class;
		DuckClass = DuckBPClass.Class;
	}
	
	bUseSeamlessTravel = true;
}

void APJEInGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	for(TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if(PlayerStart)
		{
			GameStartTransform = PlayerStart->GetTransform();
		}
	}
	
	InitializePlayer();
}

void APJEInGameMode::SetPlayerControllerClass()
{
	PlayerControllerClass = APJEPlayerController::StaticClass();
}

void APJEInGameMode::InitializePlayer()
{
	for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if(PlayerController)
		{
			APJEPlayerState* PlayerState = PlayerController->GetPlayerState<APJEPlayerState>();
			if(PlayerState)
			{
				switch(PlayerState->GetPlayerRole())
				{
				case EPlayerRole::Cat:
					PlayerClass = CatClass;
					break;
				case EPlayerRole::Duck:
					PlayerClass = DuckClass;
					break;
				}

				FActorSpawnParameters SpawnParams;
				APJECharacterPlayer* NewCharacter = GetWorld()->SpawnActor<APJECharacterPlayer>(
					PlayerClass, GameStartTransform.GetLocation(), GameStartTransform.GetRotation().Rotator(), SpawnParams);

				PlayerController->Possess(NewCharacter);
				//Cast<APJEPlayerController>(PlayerController)->InitInputPawn();
			}
		}
	}

}

void APJEInGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	if(GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Emerald, FString::Printf(TEXT("Seamless Travel Complete")));
}

