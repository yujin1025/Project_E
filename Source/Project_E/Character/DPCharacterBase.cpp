// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gimmick/New/InteractiveActor.h"
#include "Net/UnrealNetwork.h"

ADPCharacterBase::ADPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Component
	GetCapsuleComponent()->SetCollisionProfileName(FName("Player"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	InteractionTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Trigger"));
	InteractionTrigger->SetupAttachment(RootComponent);

	// Movement
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 700, 0);
	GetCharacterMovement()->GravityScale = 2.3f;
	GetCharacterMovement()->AirControl = 0.35f;
}

void ADPCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADPCharacterBase, bIsDash);
}

void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dash Logic
	if(bIsDash)
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed * 1.5f;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = Speed;
	}

	MarkWidget();
	FindClosestInteractiveActor();
}

// Find Closest Interactive Actor
void ADPCharacterBase::FindClosestInteractiveActor()
{
	
}

// Activate & DisActivate Widgets
void ADPCharacterBase::MarkWidget()
{
	if(!IsLocallyControlled()) return;
	
	TArray<AActor*> CurrentOverlappingActors;

	InteractionTrigger->GetOverlappingActors(CurrentOverlappingActors, AInteractiveActor::StaticClass());
	for(auto CurrentActor : CurrentOverlappingActors)
	{
		if(!InteractiveActors.Contains(CurrentActor))
		{
			InteractiveActors.Add(CurrentActor);
		}
	}
	
	float ClosestActorDist = 100.f;
	if(ClosestActor)
	{
		if(this->GetDistanceTo(ClosestActor) > 100.f)
		{
			Server_Interrupt(ClosestActor);
		}
		ClosestActor->DisplayInteractionWidget(false);
		ClosestActor = nullptr;
	}

	TArray<AActor*> TempInteractiveActors;
	for(auto CurrentActor : InteractiveActors)
	{
		if(!CurrentActor)
		{
			continue;
		}

		AInteractiveActor* InteractiveActor = Cast<AInteractiveActor>(CurrentActor);
		
		float TDist = this->GetDistanceTo(InteractiveActor);
		if(TDist > InteractionTrigger->GetScaledSphereRadius())
		{
			InteractiveActor->DisplayNotifyWidget(false);
			InteractiveActor->DisplayInteractionWidget(false);
			continue;
		}

		if(TDist < ClosestActorDist)
		{
			ClosestActor = Cast<AInteractiveActor>(InteractiveActor);
			ClosestActorDist = TDist;
		}
		InteractiveActor->DisplayNotifyWidget(true);
		TempInteractiveActors.Add(InteractiveActor);
	}
	InteractiveActors = TempInteractiveActors;

	if(ClosestActor)
	{
		ClosestActor->DisplayInteractionWidget(true);
	}
}



// Dash
void ADPCharacterBase::Dash(bool bDash)
{
	Server_Dash(bDash);
}

void ADPCharacterBase::Drop()
{
	
}

void ADPCharacterBase::Server_Dash_Implementation(bool bDash)
{
	bIsDash = bDash;
}

// Interact
void ADPCharacterBase::InteractBegin()
{
	Server_InteractBegin(ClosestActor);
}

void ADPCharacterBase::Server_InteractBegin_Implementation(AInteractiveActor* IActor)
{
	if(IActor && IActor->GetIsInteractAble())
	{
		IActor->InteractionKeyPressed();
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, FString::Printf(TEXT("Interact Key Pressed")));
	}
}

void ADPCharacterBase::InteractEnd()
{
	Server_InteractEnd(ClosestActor);
}

void ADPCharacterBase::Server_InteractEnd_Implementation(AInteractiveActor* IActor)
{
	if(IActor && IActor->GetIsInteractAble())
	{
		IActor->InteractionKeyReleased();
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, FString::Printf(TEXT("Interact Key Released")));
	}
}

void ADPCharacterBase::Server_Interrupt_Implementation(AInteractiveActor* IActor)
{
	if(IActor && IActor->GetIsInteractAble())
	{
		IActor->BreakInteracting();
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Emerald, FString::Printf(TEXT("Break Interacting")));
	}
}

// Jump
void ADPCharacterBase::Jump()
{
	Super::Jump();
	
	if(JumpCount < 2)
	{
		JumpCount++;
		LaunchCharacter(FVector(0,0,JumpHeight), false, true);
	}
}

void ADPCharacterBase::Falling()
{
	Super::Falling();

	JumpStartHeight = GetActorLocation().Z;
}

void ADPCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	JumpCount = 0;

	FVector Velocity = GetVelocity();
	float JumpEndHeight = GetActorLocation().Z;
	float DropHeight = JumpStartHeight - JumpEndHeight;
	
	if(Velocity.Z < -1600.f || DropHeight > 500.f)
	{
		// Death Leap Logic
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Death Leap")));
	}
}


