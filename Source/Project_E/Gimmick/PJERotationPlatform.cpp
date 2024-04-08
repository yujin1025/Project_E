

#include "Gimmick/PJERotationPlatform.h"

UPJERotationPlatform::UPJERotationPlatform()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPJERotationPlatform::BeginPlay()
{
	Super::BeginPlay();
}


void UPJERotationPlatform::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RotatePlatform(DeltaTime);
}

void UPJERotationPlatform::RotatePlatform(float Deltatime)
{
	GetOwner()->AddActorWorldRotation(FRotator(0.f, 0.f, RotationSpeed * RotationOffset * Deltatime));
}