// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/IgnitionHandle.h"

#include "EnhancedInputComponent.h"
#include "PJECamPos.h"
#include "PJERotateComponent.h"
#include "PJERotatingPlatform.h"
#include "Character/PJECharacterPlayer.h"
#include "Net/UnrealNetwork.h"
#include "Player/PJEPlayerController.h"

// Sets default values
AIgnitionHandle::AIgnitionHandle()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractType = EInteractType::Control;
	
	SwitchPivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	SwitchPivot->SetupAttachment(Root);
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetGenerateOverlapEvents(false);
	BaseMesh->SetupAttachment(SwitchPivot);
	
	RotateComponent = CreateDefaultSubobject<UPJERotateComponent>(TEXT("Rotate Component"));
	RotateComponent->SetRotateTarget(SwitchPivot);
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

	if(!bIsInteractAble || bIsInteracting) return;
	
	//TimeAfterInput = 0.f;
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
	if(HasAuthority())
	{
		bIsInteracting = false;
	}
	else
	{
		ServerInteractionEnd();
	}
	
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

void AIgnitionHandle::ServerInteractionEnd_Implementation()
{
	bIsInteracting = false;
}

void AIgnitionHandle::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &AIgnitionHandle::DoRotation);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &AIgnitionHandle::StopRotation);
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &AIgnitionHandle::ReturnPawn);
}

void AIgnitionHandle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentRotateState);
	DOREPLIFETIME(ThisClass, RotateSpeed);
}


void AIgnitionHandle::NotifyPlatform(ERotateState RotateState, float Speed)
{
	RotateComponent->SetRotateState(RotateState);
	RotateComponent->SetRotationSpeed(Speed);
	
	for(auto RotatingPlatform : RotatingPlatforms)
	{
		UPJERotateComponent* RotateComp = RotatingPlatform->GetRotationComponent();
		RotateComp->SetRotateState(RotateState);
		RotateComp->SetRotationSpeed(Speed);
	}
}

void AIgnitionHandle::DoRotation(const FInputActionValue& Value)
{
	if(HasAuthority())
	{
		CurrentRotateState = ERotateState::Rotating;
		RotateSpeed = Value.Get<float>() * 10.f;
	}
	else
	{
		float Speed = Value.Get<float>() * 10.f;
		ServerDoRotation(Speed);
	}
}

void AIgnitionHandle::ServerDoRotation_Implementation(const float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Server Rotation On"))
	CurrentRotateState = ERotateState::Rotating;
	RotateSpeed = Speed;
	UE_LOG(LogTemp, Warning, TEXT("Rotation Speed : %f"), RotateSpeed);
	
}

void AIgnitionHandle::StopRotation()
{
	if(HasAuthority())
		CurrentRotateState = ERotateState::Interrupt;
	else
		ServerStopRotation();
}

void AIgnitionHandle::ServerStopRotation_Implementation()
{
	CurrentRotateState = ERotateState::Interrupt;
}
