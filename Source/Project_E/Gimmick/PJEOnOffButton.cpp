// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEOnOffButton.h"

APJEOnOffButton::APJEOnOffButton()
{
	// Add Interaction Widget
}

void APJEOnOffButton::ShowInteractWidget()
{
	// Enable Interaction
}

void APJEOnOffButton::HideInteractWidget()
{
	// Disable Interaction
}

void APJEOnOffButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
										UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Super::ButtonBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Hit);

	// a. Show Interaction UI
	// b. Enable Interaction
	ShowInteractWidget();
}

void APJEOnOffButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ButtonEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	// a. Hide Interaction UI
	// b. Disable Interaction
	HideInteractWidget();
}

void APJEOnOffButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// TODO: Make Interact
// Interaction Key is [E] (can be changed)
// if Interact..
// a. When bButtonInteract is false -> set bButtonInteract true
// b. When bButtonInteract is true -> set bButtonInteract false
