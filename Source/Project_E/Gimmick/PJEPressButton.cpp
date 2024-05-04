// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEPressButton.h"

#include "Components/BoxComponent.h"

void APJEPressButton::BeginPlay()
{
	Super::BeginPlay();

	ButtonTrigger->OnComponentBeginOverlap.AddDynamic(this, &APJEPressButton::ButtonBeginOverlap);
	ButtonTrigger->OnComponentEndOverlap.AddDynamic(this, &APJEPressButton::ButtonEndOverlap);
}

void APJEPressButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	bIsInteracting = true;
}

void APJEPressButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bIsInteracting = false;
}


void APJEPressButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}
