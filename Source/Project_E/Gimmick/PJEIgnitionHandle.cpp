// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEIgnitionHandle.h"

#include "PJERotationPlatform.h"

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
		for(auto CurrentPlatform:RotationPlatforms)
		{
			if(TObjectPtr<UPJERotationPlatform> RotationPlatform = Cast<UPJERotationPlatform>(CurrentPlatform))
			{
				RotationPlatform->SetRotationOffset(1);
			}
		}
	}
}

void APJEIgnitionHandle::OperateCounterClockwiseTurn()
{
	if(!RotationPlatforms.IsEmpty())
	{
		for(auto CurrentPlatform:RotationPlatforms)
		{
			if(TObjectPtr<UPJERotationPlatform> RotationPlatform = Cast<UPJERotationPlatform>(CurrentPlatform))
			{
				RotationPlatform->SetRotationOffset(-1);
			}
		}
	}
}

void APJEIgnitionHandle::IntteruptRotation()
{
	if(!RotationPlatforms.IsEmpty())
	{
		for(auto CurrentPlatform:RotationPlatforms)
		{
			if(TObjectPtr<UPJERotationPlatform> RotationPlatform = Cast<UPJERotationPlatform>(CurrentPlatform))
			{
				RotationPlatform->SetRotationOffset(0);
			}
		}
	}
}

void APJEIgnitionHandle::SetCharacter(APJECharacterPlayer* PlayerCharacter)
{
	Character = PlayerCharacter;
}

