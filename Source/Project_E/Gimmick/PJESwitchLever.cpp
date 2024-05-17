#include "Gimmick/PJESwitchLever.h"

APJESwitchLever::APJESwitchLever()
{
	LeverBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	LeverBaseMesh->SetupAttachment(RootComponent);
	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	LeverMesh->SetupAttachment(LeverBaseMesh);
}

void APJESwitchLever::BeginPlay()
{
	Super::BeginPlay();
}

void APJESwitchLever::InteractionKeyReleased()
{
	Super::InteractionKeyReleased();

	ActivateLever();
}

void APJESwitchLever::ActivateLever()
{
	if(!bIsActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("Lever On"));
		bIsActive = true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lever Off"));
		bIsActive = false;
	}
}

void APJESwitchLever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
