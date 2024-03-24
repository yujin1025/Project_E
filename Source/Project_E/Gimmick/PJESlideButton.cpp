// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJESlideButton.h"

APJESlideButton::APJESlideButton()
{
	
}

void APJESlideButton::BeginInteracting()
{
	Super::BeginInteracting();

	bIsInteracting = true;
}

void APJESlideButton::EndInteracting()
{
	Super::EndInteracting();

	bIsInteracting = false;
}
