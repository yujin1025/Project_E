// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJESlideButton.h"

APJESlideButton::APJESlideButton()
{
	
}

void APJESlideButton::BeginInteracting(const AActor* InteractActor)
{
	Super::BeginInteracting(InteractActor);

	bIsInteracting = true;
}

void APJESlideButton::EndInteracting(const AActor* InteractActor)
{
	Super::EndInteracting(InteractActor);

	bIsInteracting = false;
}
