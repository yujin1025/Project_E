// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PJEGameModeBase.h"
#include "../UI/BaseWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Player/PJEPlayerController.h>

APJEGameModeBase::APJEGameModeBase()
{
}

void APJEGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	OpenWidget();
}

void APJEGameModeBase::OnPlayerDead(int PlayerNumber)
{
	APJEPlayerController* PlayerController = Cast<APJEPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), PlayerNumber));
	if (PlayerController)
	{
		PlayerController->GameOver();
	}
}

void APJEGameModeBase::OpenWidget()
{
	InGameWindowWidget = CreateWidget<UBaseWidget>(GetWorld(), InGameWindowWidgetClass);
	if (InGameWindowWidget != nullptr)
	{
		InGameWindowWidget->AddToViewport();
	}
}
