// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEPressButton.h"

void APJEPressButton::BeginPlay()
{
	Super::BeginPlay();

	
}

void APJEPressButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Super::ButtonBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Hit);
	
	bButtonInteract = true;
}

void APJEPressButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ButtonEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	bButtonInteract = false;
}
