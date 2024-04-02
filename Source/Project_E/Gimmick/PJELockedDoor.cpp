// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJELockedDoor.h"

#include "Character/PJECharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
APJELockedDoor::APJELockedDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	SetRootComponent(DoorMesh);
	DoorMesh->SetGenerateOverlapEvents(false);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	Widget->SetupAttachment(DoorMesh);

	InteractTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	InteractTrigger->SetupAttachment(DoorMesh);
}

// Called when the game starts or when spawned
void APJELockedDoor::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);
	OriginLocation = DoorMesh->GetRelativeLocation();
}

/** Interact Interface */

void APJELockedDoor::ShowInteractWidget()
{
	IPJEInteractInterface::ShowInteractWidget();

	Widget->SetVisibility(true);
}

void APJELockedDoor::HideInteractWidget()
{
	IPJEInteractInterface::HideInteractWidget();

	Widget->SetVisibility(false);
}

void APJELockedDoor::BeginInteracting(const AActor* InteractActor)
{
	IPJEInteractInterface::BeginInteracting(InteractActor);
}

void APJELockedDoor::EndInteracting(const AActor* InteractActor)
{
	IPJEInteractInterface::EndInteracting(InteractActor);

	bIsUnlocking = CheckValidKey(InteractActor);
	if(bIsUnlocking)
	{
		UE_LOG(LogTemp, Warning, TEXT("Door Open!"));
		bIsInteractable = false;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Matching Key!"));
	}
}

/** End Interact Interface */

void APJELockedDoor::MoveDoor(float DeltaTime)
{
	FVector CurrentLocation = DoorMesh->GetRelativeLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;

	// Moving door based on whether it's interactive or not
	if(bIsUnlocking)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Button Active"));
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		DoorMesh->SetRelativeLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		DoorMesh->SetRelativeLocation(NewLocation);
	}
}

bool APJELockedDoor::CheckValidKey(const AActor* InteractActor)
{
	AActor* NCInteractActor = const_cast<AActor*>(InteractActor);
	APJECharacterPlayer* InteractCharacter = Cast<APJECharacterPlayer>(NCInteractActor);
	if(IsValid(InteractCharacter))
	{
		int32 PlayerHandItem = InteractCharacter->GetHandItemCode();
		
		if(PlayerHandItem == UnlockingKeyCode)
		{
			bIsUnlocking = true;
			bIsInteractable = false;
			return true;
		}
	}
	return false;
}



void APJELockedDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveDoor(DeltaTime);
}

