// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEPressButton.h"

#include "PJEMovingComponent.h"
#include "PJEPlatform.h"

APJEPressButton::APJEPressButton()
{
	ButtonBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base"));
	ButtonBaseMesh->SetupAttachment(RootComponent);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(ButtonBaseMesh);

	MovingComponent = CreateDefaultSubobject<UPJEMovingComponent>(TEXT("Moving Component"));
}

void APJEPressButton::BeginPlay()
{
	MovingComponent->SetMovementTarget(ButtonMesh);
	Super::BeginPlay();
}

void APJEPressButton::ActivateButton()
{
	bool bTemp = bIsInteracting;
	bIsInteracting = bIsPlayerNearby;
	if(bTemp != bIsInteracting)
	{
		if(bIsInteracting)
		{
			MovingComponent->SetMovementState(EMovementState::Moving);
		}
		else
		{
			MovingComponent->SetMovementState(EMovementState::Returning);
		}
	}
}

void APJEPressButton::CheckActive()
{
	bool bTemp = bIsActive;
	bIsActive = MovingComponent->bIsArrived;
	if(bTemp != bIsActive)
	{
		if(bIsActive)
		{
			NotifyPlatform(true);
		}
		else
		{
			NotifyPlatform(false);
		}
	}
}

void APJEPressButton::NotifyPlatform(bool bActive)
{
	if(!Platforms.IsEmpty())
	{
		for(auto Platform:Platforms)
		{
			Platform->SetbPlatformActive(bIsActive);
		}
	}
}

void APJEPressButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ActivateButton();
	CheckActive();
}
