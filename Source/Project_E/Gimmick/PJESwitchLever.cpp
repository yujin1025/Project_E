#include "Gimmick/PJESwitchLever.h"

#include "PJEPlatform.h"
#include "PJERotateComponent.h"

APJESwitchLever::APJESwitchLever()
{
	LeverBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Base"));
	LeverBaseMesh->SetupAttachment(RootComponent);
	LeverPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Lever Pivot"));
	LeverPivot->SetupAttachment(LeverBaseMesh);
	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever"));
	LeverMesh->SetupAttachment(LeverPivot);

	RotateComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotate Component"));
}

void APJESwitchLever::BeginPlay()
{
	RotateComponent->SetRotateTarget(LeverPivot);
	Super::BeginPlay();
}

void APJESwitchLever::InteractionKeyReleased()
{
	Super::InteractionKeyReleased();

	ActivateLever();
}

void APJESwitchLever::ActivateLever()
{
	if(!bIsInteracting)
	{
		bIsInteracting = true;
		RotateComponent->SetRotateState(ERotateState::Rotating);
	}
	else
	{
		bIsInteracting = false;
		RotateComponent->SetRotateState(ERotateState::Returning);
	}
}

void APJESwitchLever::CheckActive()
{
	bool bTemp = bIsActive;
	bIsActive = RotateComponent->bIsMaxRotate;
	if(bTemp != bIsActive)
	{
		if(bIsActive)
		{
			NotifyPlatform(true);
		}
		else
		{
			NotifyPlatform(false);
		}
	}
}

void APJESwitchLever::NotifyPlatform(bool bActive)
{
	if(!Platforms.IsEmpty())
	{
		for(auto Platform:Platforms)
		{
			Platform->SetbPlatformActive(bActive);
		}
	}
}

void APJESwitchLever::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	CheckActive();
}
