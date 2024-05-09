// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

APJEPlayerController::APJEPlayerController()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/PC/BP_Cat"));
	if(PlayerPawnBPClass.Class != NULL)
	{
		PlayableCharacterClass = PlayerPawnBPClass.Class;
	}
}

void APJEPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerStart();

	// PlayerPawn을 PlayerStart 위치에 생성
	PlayerPawn = GetWorld()->SpawnActor<APawn>(PlayableCharacterClass, SpawnLocation, SpawnRotation);
	Possess(PlayerPawn);	
}

void APJEPlayerController::SwitchInputToIgnitionHandle()
{
	
}

void APJEPlayerController::SwitchInputToPlayer()
{
	
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
