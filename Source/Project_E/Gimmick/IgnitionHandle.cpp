// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/IgnitionHandle.h"

#include "PJERotateComponent.h"
#include "PJERotatingPlatform.h"

// Sets default values
AIgnitionHandle::AIgnitionHandle()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractType = EInteractType::Control;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetGenerateOverlapEvents(false);
	BaseMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AIgnitionHandle::BeginPlay()
{
	Super::BeginPlay();

	LastRotateState = ERotateState::Interrupt;
	CurrentRotateState = ERotateState::Interrupt;
}

void AIgnitionHandle::NotifyPlatform(ERotateState RotateState, float Speed)
{
	for(auto RotatingPlatform : RotatingPlatforms)
	{
		UPJERotateComponent* RotateComponent = RotatingPlatform->GetRotationComponent();
		RotateComponent->SetRotateState(RotateState);
		RotateComponent->SetRotationSpeed(Speed);
	}
}

void AIgnitionHandle::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	TimeAfterInput = 0.f;

	// 플레이어컨트롤러에 새로운 입력방식 할당
}

void AIgnitionHandle::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	// 플레이어컨트롤러에 원래 입력방식 할당
}

// Called every frame
void AIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentRotateState != LastRotateState)
	{
		NotifyPlatform(CurrentRotateState, 10.f);
	}
	LastRotateState = CurrentRotateState;

	if(CurrentRotateState != ERotateState::Rotating)
	{
		TimeAfterInput += DeltaTime;
		if(TimeAfterInput >= DelayTime)
		{
			CurrentRotateState = ERotateState::Returning;
		}
	}
}

