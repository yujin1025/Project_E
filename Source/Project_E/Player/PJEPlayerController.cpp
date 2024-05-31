// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "Character/PJECharacterPlayer.h"
#include "GameFramework/PlayerStart.h"
#include "Gimmick/PJEInputInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"


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

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(PlayerController)
	{
		APawn* PossessPawn = PlayerController->GetPawn();
		if(PossessPawn)
		{
			
		}
		else
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Yellow,
				FString(TEXT("No Possessed Pawn"))
				);
			}
			PlayerController->Possess(PlayerPawn);
		}
	}
	
	
	/*
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
	LastBindingActor = CurrentBindingActor;*/
}

void APJEPlayerController::SwitchInputToOther()
{
	IPJEInputInterface* InputInterface = Cast<IPJEInputInterface>(CurrentBindingActor);
	if(InputInterface)
	{
		InputInterface->SetupInputBinding(this);
	}
}

void APJEPlayerController::SwitchInputToPawn()
{
	APJECharacterPlayer* PlayerCharacter = Cast<APJECharacterPlayer>(PlayerPawn);
	if(PlayerCharacter)
	{
		PlayerCharacter->SetupPlayerInputComponent(PlayerCharacter->InputComponent);
	}
}

void APJEPlayerController::OnPossessCharacter(APJECharacterBase* aCharacter)
{
	this->OwnerCharacter = aCharacter;
}

APJECharacterBase* APJEPlayerController::GetCharacter()
{
	return OwnerCharacter;
}


void APJEPlayerController::GameOver()
{
}
