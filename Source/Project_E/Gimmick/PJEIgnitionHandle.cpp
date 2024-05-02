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
}

void APJEIgnitionHandle::SetPlatformOptions(float Speed, bool bRotate)
{
	for(auto Platform:RotationPlatforms)
	{
		Platform->SetRotationComponent(Speed, bRotate);
	}
}

void APJEIgnitionHandle::ResetRotation()
{
}

void APJEIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(LastHandleInt != HandleInt)
	{
		switch(HandleInt)
		{
		case -1:
			SetPlatformOptions(-1, true);
			break;
		case 0:
			SetPlatformOptions(0, false);
			break;
		case 1:
			SetPlatformOptions(1, true);
			break;
		default:
			break;
		}
	}

	LastHandleInt = HandleInt;
}
