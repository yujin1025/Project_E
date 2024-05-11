// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerState.h"

APJEPlayerState::APJEPlayerState()
{
}

void APJEPlayerState::OnChangePlayerHealth(int objectId, float Amount)
{
	OnPlayerHPChanged.Broadcast(objectId, Amount);

	if (Amount <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Destroyed!"));
	}
}
