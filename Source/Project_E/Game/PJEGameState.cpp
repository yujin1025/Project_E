// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEGameState.h"

APJEGameState::APJEGameState()
{
}

void APJEGameState::OnChangedHealth(int ObjectID, float Amount)
{
	if (Amount <= 0.0f)
	{
		AActor* Actor = GetOwner();
		if (Actor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Monster Destroyed!"));
		}
	}
}
