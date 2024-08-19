// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterNonPlayer.h"
#include "AI/PJEAIController.h"

APJECharacterNonPlayer::APJECharacterNonPlayer()
{
	AIControllerClass = APJEAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void APJECharacterNonPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APJECharacterNonPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void APJECharacterNonPlayer::SetDead()
{
	Super::SetDead();

	APJEAIController* ABAIController = Cast<APJEAIController>(GetController());
	if (ABAIController)
	{
		ABAIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}