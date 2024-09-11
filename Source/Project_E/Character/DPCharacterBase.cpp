// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ADPCharacterBase::ADPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Component
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

void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADPCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpCount = 0;
}

void ADPCharacterBase::Jump()
{
	Super::Jump();

	if(JumpCount < 2)
	{
		JumpCount++;
		LaunchCharacter(FVector(0,0,JumpHeight), false, true);
	}
}

void ADPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
