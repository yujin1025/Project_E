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
	LeverMesh->SetIsReplicated(true);

	RotateComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotate Component"));
}

void APJESwitchLever::BeginPlay()
{
	RotateComponent->SetRotateTarget(LeverPivot);
	Super::BeginPlay();
}

void APJESwitchLever::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	ActivateLever();
}

void APJESwitchLever::ActivateLever()
{
	// 레버 동작은 서버에서만 이루어진다.
	// 클라이언트는 레버 동작의 결과를 Replicate받는다.
	if(HasAuthority())
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
