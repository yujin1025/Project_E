// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/New/PushButton.h"

APushButton::APushButton()
{
	ButtonBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Base"));
	ButtonBase->SetupAttachment(RootComponent);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(ButtonBase);

	SetInteractType(EInteractType::Hold);
}

void APushButton::BeginPlay()
{
	Super::BeginPlay();
	
	OriginButtonLocation = ButtonMesh->GetComponentLocation();
}

void APushButton::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MoveButton(DeltaSeconds);
}

void APushButton::InteractionKeyPressed()
{
	Super::InteractionKeyPressed();
	
	SetIsInteracting(true);
}

void APushButton::InteractionKeyReleased()
{
	Super::InteractionKeyReleased();

	SetIsInteracting(false);
}

void APushButton::BreakInteracting()
{
	Super::BreakInteracting();

	SetIsInteracting(false);
}

void APushButton::MoveButton(float DeltaSeconds)
{
	FVector CurrentLocation = ButtonMesh->GetComponentLocation();
	FVector TargetLocation = GetIsInteracting() ? OriginButtonLocation + ButtonMovementOffset : OriginButtonLocation;
	FVector NextLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaSeconds, ButtonMoveSpeed);
	ButtonMesh->SetWorldLocation(NextLocation);
}



