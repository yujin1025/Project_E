
#include "Gimmick/PJERotateComponent.h"

UPJERotateComponent::UPJERotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPJERotateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPJERotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bIsRotating)
	{
		GetOwner()->AddActorWorldRotation(RotationOffset * DeltaTime * RotationSpeed);
	}
}

