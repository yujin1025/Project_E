// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEInGameMode.h"

#include "EngineUtils.h"
#include "PJEPlayerState.h"
#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"
#include "GameFramework/PlayerStart.h"
#include "Player/PJEPlayerController.h"

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

	GetWorld()->GetTimerManager().SetTimer(InitDelayHandle, this, &ThisClass::InitializePlayer, 3.0f, false);
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
				SpawnParams.Owner = PlayerController;
				
				APJECharacterPlayer* NewCharacter = GetWorld()->SpawnActor<APJECharacterPlayer>(
					PlayerClass, GameStartTransform.GetLocation(), GameStartTransform.GetRotation().Rotator(), SpawnParams);

				PlayerPawns.Add(NewCharacter);
			}
		}
	}

	GetWorld()->GetTimerManager().SetTimer(ActorDelayHandle, this, &ThisClass::PossessController, 2.f, false);

}

void APJEInGameMode::PossessController()
{
	int i = 0;
	for(FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APJEPlayerController* PlayerController = Cast<APJEPlayerController>(Iterator->Get());
		if(PlayerController)
		{
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d PC Loc"), i));
			PlayerController->Client_Possess(PlayerPawns[i]);
			i++;
		}
	}
}

void APJEInGameMode::PostSeamlessTravel()
{
	Super::PostSeamlessTravel();
	if(GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Emerald, FString::Printf(TEXT("Seamless Travel Complete")));
}
