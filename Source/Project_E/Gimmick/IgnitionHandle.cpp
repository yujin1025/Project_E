// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/IgnitionHandle.h"

#include "EnhancedInputComponent.h"
#include "PJECamPos.h"
#include "PJERotateComponent.h"
#include "PJERotatingPlatform.h"
#include "Character/PJECharacterPlayer.h"
#include "Player/PJEPlayerController.h"

// Sets default values
AIgnitionHandle::AIgnitionHandle()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractType = EInteractType::Control;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetGenerateOverlapEvents(false);
	BaseMesh->SetupAttachment(Root);
}

void AIgnitionHandle::BeginPlay()
{
	Super::BeginPlay();

	LastRotateState = ERotateState::Interrupt;
	CurrentRotateState = ERotateState::Interrupt;
}

void AIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentRotateState != LastRotateState)
	{
		NotifyPlatform(CurrentRotateState, RotateSpeed);
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

void AIgnitionHandle::InteractionKeyReleased_Implementation(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);
	
	TimeAfterInput = 0.f;
	bIsInteracting = true;

	if(!Character) return;
	
	APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(Character->GetController());

	if(LocalPlayerController)
	{
		LocalPlayerController->SetOperatingActor(this);
		LocalPlayerController->InitInputIgnitionHandle();
		Character->SetCamLocationRotation(Campos->GetArrowLocation(), Campos->GetArrowRotation());
	}
}

void AIgnitionHandle::ReturnPawn()
{
	bIsInteracting = false;
	
	UWorld* World = GetWorld();
	if(World)
	{
		APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(World->GetFirstPlayerController());
		if(LocalPlayerController)
		{
			LocalPlayerController->SetOperatingActor(nullptr);
			LocalPlayerController->InitInputPawn();
			
			APJECharacterPlayer* Player = Cast<APJECharacterPlayer>(LocalPlayerController->GetPawn());
			if(Player && Campos)
			{
				Player->BackCamera();
			}
		}
	}
}

void AIgnitionHandle::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &AIgnitionHandle::DoRotation);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &AIgnitionHandle::StopRotation);
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &AIgnitionHandle::ReturnPawn);
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

void AIgnitionHandle::DoRotation(const FInputActionValue& Value)
{
	CurrentRotateState = ERotateState::Rotating;

	RotateSpeed = Value.Get<float>() * 10.f;
}

void AIgnitionHandle::StopRotation()
{
	CurrentRotateState = ERotateState::Interrupt;
}