// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEPlatform.h"

APJEPlatform::APJEPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = PlatformMesh;
}

void APJEPlatform::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetActorLocation();
}

void APJEPlatform::MovePlatform(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;
	
	if(bPlatformActive)
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		SetActorLocation(NewLocation);
		AfterDisactive = 0.f;
	}
	else
	{
		AfterDisactive += DeltaTime;
		
		// Return the platform to its original location after
		// a period of time has passed since the player stopped interacting with button
		if(AfterDisactive > PlatformDelayTime)
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
			SetActorLocation(NewLocation);
		}
	}
}

void APJEPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
}