// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEIgnitionHandle.h"
#include "Gimmick/PJEIgnitionHandle.h"

#include "PJERotateComponent.h"

// Sets default values
APJEIgnitionHandle::APJEIgnitionHandle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APJEIgnitionHandle::BeginPlay()
{
	Super::BeginPlay();

	OperateClockwiseTurn();
}

// Called every frame
void APJEIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APJEIgnitionHandle::BindInput()
{
	if(!Character)
	{
		return;
	}
	
}


void APJEIgnitionHandle::OperateClockwiseTurn()
{
	if(!RotationPlatforms.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Empty"));
		for(auto CurrentPlatform:RotationPlatforms)
		{
			if(TObjectPtr<UPJERotateComponent> RotationPlatform = Cast<UPJERotateComponent>(CurrentPlatform))
			{
				UE_LOG(LogTemp, Warning, TEXT("Cast Succeed"));
				RotationPlatform->SetRotationSpeed(1);
				RotationPlatform->SetIsRotating(true);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cast Faild"));
			}
		}
	}
}

void APJEIgnitionHandle::OperateCounterClockwiseTurn()
{
	if(RotationPlatforms.IsEmpty())
	{
		return;
	}
	for(auto CurrentPlatform:RotationPlatforms)
	{
		if(TObjectPtr<UPJERotateComponent> RotationPlatform = Cast<UPJERotateComponent>(CurrentPlatform))
		{
			RotationPlatform->SetRotationSpeed(-1);
			RotationPlatform->SetIsRotating(true);
		}
	}
}

void APJEIgnitionHandle::InterruptRotation()
{
	if(!RotationPlatforms.IsEmpty())
	{
		for(auto CurrentPlatform:RotationPlatforms)
		{
			if(TObjectPtr<UPJERotateComponent> RotationPlatform = Cast<UPJERotateComponent>(CurrentPlatform))
			{
				RotationPlatform->SetRotationSpeed(0);
				RotationPlatform->SetIsRotating(false);
			}
		}
	}
}

void APJEIgnitionHandle::SetCharacter(APJECharacterPlayer* PlayerCharacter)
{
	Character = PlayerCharacter;
}

