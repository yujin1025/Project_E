// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

void ADPCharacterBase::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpCount = 0;
}