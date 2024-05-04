#include "PJEIgnitionHandle.h"
#include "PJERotateComponent.h"

#include "PJERotatingPlatform.h"

APJEIgnitionHandle::APJEIgnitionHandle()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APJEIgnitionHandle::BeginPlay()
{
	Super::BeginPlay();

	LastRotateState = ERotateState::Interrupt;
	CurrentRotateState = ERotateState::Interrupt;
}

void APJEIgnitionHandle::NotifyState(ERotateState RotateState)
{
	for(auto RotationPlatform: RotationPlatforms)
	{
		UPJERotateComponent* RotateComponent = RotationPlatform->GetRotationComponent();
		RotateComponent->SetRotateState(RotateState);
	}
}

void APJEIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentRotateState != LastRotateState)
	{
		NotifyState(CurrentRotateState);
	}
	LastRotateState = CurrentRotateState;
}
