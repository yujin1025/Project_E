// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEOnOffLever.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
APJEOnOffLever::APJEOnOffLever()
{
	PrimaryActorTick.bCanEverTick = true;

	LeverBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeverBase"));
	SetRootComponent(LeverBaseMesh);
	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	LeverMesh->SetupAttachment(LeverBaseMesh);

	InteractableBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Interactable Box"));
	ShowInteractableWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interactable Widget"));
}

// Called when the game starts or when spawned
void APJEOnOffLever::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APJEOnOffLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

