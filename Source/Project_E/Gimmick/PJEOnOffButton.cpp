// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEOnOffButton.h"

APJEOnOffButton::APJEOnOffButton()
{
	// Add Interaction Widget
}

/** Interact: Can Interact when the previous action end */
void APJEOnOffButton::BeginInteracting(const AActor* InteractActor)
{
	Super::BeginInteracting(InteractActor);
}

void APJEOnOffButton::EndInteracting(const AActor* InteractActor)
{
	Super::EndInteracting(InteractActor);

	if(bIsInteracting)
	{
		bIsInteracting = false;
	}
	else
	{
		bIsInteracting = true;
	}
}


void APJEOnOffButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
