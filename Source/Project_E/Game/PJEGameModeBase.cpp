// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <Player/PJEPlayerController.h>

APJEGameModeBase::APJEGameModeBase()
{
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
