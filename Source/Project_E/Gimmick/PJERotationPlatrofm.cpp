// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJERotationPlatrofm.h"

#include "PJERotateComponent.h"

APJERotationPlatrofm::APJERotationPlatrofm()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	SetRootComponent(PlatformMesh);
	RotationComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotation Component"));
}

void APJERotationPlatrofm::BeginPlay()
{
	Super::BeginPlay();
	
}

void APJERotationPlatrofm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

