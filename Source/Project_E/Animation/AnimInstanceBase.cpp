// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstanceBase.h"

#include "Character/DPCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAnimInstanceBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ADPCharacterBase>(TryGetPawnOwner());
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(Character == nullptr)
	{
		Character = Cast<ADPCharacterBase>(TryGetPawnOwner());
	}
	if(!Character) return;

	// Set Speed
	FVector Velocity = Character->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	// Set Is In Air
	bIsInAir = Character->GetCharacterMovement()->IsFalling();

	// Set Is Accelerating
	bIsAccelerating = Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;

	// Calculate Rotation
	FRotator ActorRotation = Character->GetActorRotation();
	FRotator VelocityRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

	// Set Direction
	FRotator DirectionDeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator(ActorRotation, VelocityRotation);
	Direction = DirectionDeltaRotation.Yaw * (-1.f);
}
