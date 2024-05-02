
#include "Gimmick/PJERotatingPlatform.h"

#include "PJERotateComponent.h"

APJERotatingPlatform::APJERotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	RootComponent = PlatformMesh;

	RotationComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotation Component"));
}

void APJERotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	OriginRotation = GetActorRotation();
}

// Called every frame
void APJERotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APJERotatingPlatform::SetRotationComponent(float Speed, bool bRotate)
{
	RotationComponent->SetRotationSpeed(Speed);
	RotationComponent->SetIsRotating(bRotate);
}