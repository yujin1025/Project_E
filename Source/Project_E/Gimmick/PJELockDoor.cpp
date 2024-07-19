// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJELockDoor.h"

#include "PJEMovingComponent.h"

APJELockDoor::APJELockDoor()
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorMesh->SetupAttachment(RootComponent);
	
	MovingComponent = CreateDefaultSubobject<UPJEMovingComponent>(TEXT("Moving Component"));
}

void APJELockDoor::BeginPlay()
{
	MovingComponent->SetMovementTarget(DoorMesh);
	Super::BeginPlay();
}

void APJELockDoor::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);
	
	int32 CharacterHandItemcode = 0;
	//Character에 접근하여 손에 들고 있는 Item의 Code를 얻어낸다
	bIsInteracting = CheckValidKey(CharacterHandItemcode);
	if(bIsInteracting)
	{
		MovingComponent->SetMovementState(EMovementState::Moving);
	}
}

bool APJELockDoor::CheckValidKey(int32 Itemcode)
{
	if(Itemcode == UnlockKeycode)
	{
		DisableInteraction();
		return true;
		// 상호작용 불가능하게 코드 추가하기
	}
	return false;
}

void APJELockDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
