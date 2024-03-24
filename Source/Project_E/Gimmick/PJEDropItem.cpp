// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEDropItem.h"

#include "UnrealWidgetFwd.h"
#include "Components/BoxComponent.h"

// Sets default values
APJEDropItem::APJEDropItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetGenerateOverlapEvents(false);
	
	WidgetTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTrigger->SetupAttachment(ItemMesh);
	
}

void APJEDropItem::BeginInteracting()
{
	IPJEInteractInterface::BeginInteracting();
}

void APJEDropItem::EndInteracting()
{
	IPJEInteractInterface::EndInteracting();
}

void APJEDropItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void APJEDropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

