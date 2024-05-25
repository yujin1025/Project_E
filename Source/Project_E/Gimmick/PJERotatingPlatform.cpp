
#include "Gimmick/PJERotatingPlatform.h"

#include "PJERotateComponent.h"

APJERotatingPlatform::APJERotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Rotating Platform"));
	RootComponent = Root;
	
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	PlatformMesh->SetupAttachment(RootComponent);
	
	RotationComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotation Component"));
}

void APJERotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	RotationComponent->SetRotateTarget(PlatformMesh);	
}

// Called every frame
void APJERotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}