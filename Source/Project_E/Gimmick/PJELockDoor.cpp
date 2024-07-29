// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJELockDoor.h"

#include "PJEMovingComponent.h"
#include "Net/UnrealNetwork.h"

APJELockDoor::APJELockDoor()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(RootComponent);
	
	MovingComponent = CreateDefaultSubobject<UPJEMovingComponent>(TEXT("Moving Component"));
	MovingComponent->SetIsReplicated(true);
}

void APJELockDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bIsKeyInserted);
}

void APJELockDoor::BeginPlay()
{
	MovingComponent->SetMovementTarget(DoorMesh);
	Super::BeginPlay();
}

// First Interaction - Insert the Key
// Second Interaction - Open the Door
void APJELockDoor::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	if(!bIsKeyInserted)
	{
		int32 CharacterHandItemCode = 0;
		if(CheckValidKey(CharacterHandItemCode))
		{
			bIsKeyInserted = true;
			// Destroy Character Item
		}
	}
	else
	{
		NetMulticast_OpenDoor();
	}
	
}

void APJELockDoor::NetMulticast_OpenDoor_Implementation()
{
	MovingComponent->SetMovementState(EMovementState::Moving);
	DisableInteraction();
}

bool APJELockDoor::CheckValidKey(int32 Itemcode)
{
	if(Itemcode == UnlockKeycode)
	{
		return true;
	}
	return false;
}

void APJELockDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
