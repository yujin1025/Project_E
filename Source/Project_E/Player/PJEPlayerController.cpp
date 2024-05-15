// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "Character/PJECharacterPlayer.h"
#include "GameFramework/PlayerStart.h"
#include "Gimmick/PJEInputInterface.h"
#include "Kismet/GameplayStatics.h"

APJEPlayerController::APJEPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void APJEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 멀티 서버 선택에 따라 캐릭터 달라진다 (PlayerStart)
	
	PlayerPawn = GetPawn();

}

void APJEPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentBindingActor = Cast<APJECharacterPlayer>(PlayerPawn)->InteractActor;
	if(LastBindingActor != CurrentBindingActor)
	{
		if(CurrentBindingActor != NULL)
		{
			SwitchInputToOther();
		}
		else
		{
			SwitchInputToPawn();
		}
	}
	LastBindingActor = CurrentBindingActor;
}

void APJEPlayerController::SwitchInputToOther()
{
	IPJEInputInterface* InputInterface = Cast<IPJEInputInterface>(CurrentBindingActor);
	if(InputInterface)
	{
		//UnPossess(); // 플레이어 UnPossess
		InputInterface->SetupInputBinding(this);
	}
}

void APJEPlayerController::SwitchInputToPawn()
{
	APJECharacterPlayer* PlayerCharacter = Cast<APJECharacterPlayer>(PlayerPawn);
	if(PlayerCharacter)
	{
		//Possess(PlayerPawn);
		PlayerCharacter->SetupPlayerInputComponent(PlayerCharacter->InputComponent);
	}
}


void APJEPlayerController::GameOver()
{
}
