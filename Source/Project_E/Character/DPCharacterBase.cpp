// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "PlayerController/InGamePlayerController.h"

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
	
}

// Dash
void ADPCharacterBase::Dash(bool bDash)
{
	Server_Dash(bDash);
}

void ADPCharacterBase::Server_Dash_Implementation(bool bDash)
{
	bIsDash = bDash;
}

// Interact
void ADPCharacterBase::Interact(bool bBeginInteract)
{
	AInGamePlayerController* DPController = Cast<AInGamePlayerController>(Controller);
	if(DPController)
	{
		if(bBeginInteract)
		{
			// Begin Interact
			DPController->Client_SwitchInput(EInputType::IT_Cylinder);
		}
		else
		{
			// End Interact
			DPController->Client_SwitchInput(EInputType::IT_Player);
		}
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
	
	if(Velocity.Z < -1400.f || DropHeight > 500.f)
	{
		// Death Leap Logic
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Death Leap")));
	}
}


