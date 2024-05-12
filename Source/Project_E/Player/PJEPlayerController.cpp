// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "Character/PJECharacterPlayer.h"
#include "GameFramework/PlayerStart.h"
#include "Gimmick/PJEInputInterface.h"
#include "Kismet/GameplayStatics.h"

APJEPlayerController::APJEPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PC/BP_Cat"));
	if(PlayerPawnBPClass.Class != NULL)
	{
		PlayableCharacterClass = PlayerPawnBPClass.Class;
	}
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
	UnPossess(); // 플레이어 UnPossess

	IPJEInputInterface* InputInterface = Cast<IPJEInputInterface>(CurrentBindingActor);
	if(InputInterface)
	{
		InputInterface->SetupInputBinding(this);
	}
}

void APJEPlayerController::SwitchInputToPawn()
{
	Possess(PlayerPawn);
}

void APJEPlayerController::SetPlayerStart()
{
	// 일단 PlayerStart 위치로 시작위치 설정한다
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
	if(PlayerStarts.Num() > 0)
	{
		AActor* ChosenStart = PlayerStarts[0];

		SpawnLocation = ChosenStart->GetActorLocation();
		SpawnRotation = ChosenStart->GetActorRotation();
	}
}

void APJEPlayerController::GameOver()
{
}
