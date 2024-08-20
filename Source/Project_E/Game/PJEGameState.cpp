// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEGameState.h"

APJEGameState::APJEGameState()
{
}

void APJEGameState::OnChangedHealth(int ObjectID, float Amount)
{
	if (OnNonPlayerHPChanged.IsBound())
	{
		OnNonPlayerHPChanged.Broadcast(ObjectID, Amount);
	}
}
