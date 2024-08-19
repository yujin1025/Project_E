// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJESlideButton.h"

#include "PJEMovingComponent.h"
#include "PJEPlatform.h"

APJESlideButton::APJESlideButton()
{
	ButtonBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base"));
	ButtonBaseMesh->SetupAttachment(RootComponent);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(ButtonBaseMesh);

	MovingComponent = CreateDefaultSubobject<UPJEMovingComponent>(TEXT("Moving Component"));
}

void APJESlideButton::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	bIsInteracting = true;
}

void APJESlideButton::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	bIsInteracting = false;
}



void APJESlideButton::BeginPlay()
{
	MovingComponent->SetMovementTarget(ButtonMesh);
	Super::BeginPlay();
}

void APJESlideButton::ActivateButton()
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

void APJESlideButton::CheckActive()
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

void APJESlideButton::NotifyPlatform(bool bActive)
{
	if(!Platforms.IsEmpty())
	{
		for(auto Platform:Platforms)
		{
			Platform->SetbPlatformActive(bIsActive);
		}
	}
}

void APJESlideButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!HasAuthority()) return;
	
	ActivateButton();
	CheckActive();
}
