// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEPressButton.h"

#include "Components/BoxComponent.h"

void APJEPressButton::BeginPlay()
{
	Super::BeginPlay();
}

void APJEPressButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Get overlapped actors every tick
	TArray<AActor*> OverlappedActors;
	ButtonTrigger->GetOverlappingActors(OverlappedActors);

	// Find most appropriate Actor
	for(auto OverlappedActor:OverlappedActors)
	{
		
	}
}
