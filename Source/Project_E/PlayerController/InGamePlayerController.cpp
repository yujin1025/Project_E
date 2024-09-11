// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/InGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/DPCharacterBase.h"

void AInGamePlayerController::Client_SwitchInput_Implementation(EInputType InputType)
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		switch (InputType)
		{
		case EInputType::IT_Player:
			Subsystem->AddMappingContext(PlayerContext, 1);
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Change input to player!")));
			break;
		case EInputType::IT_Handle:
			Subsystem->AddMappingContext(HandleContext, 1);
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Change input to handle!")));
			break;
		case EInputType::IT_Cylinder:
			Subsystem->AddMappingContext(CylinderContext, 1);
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Change input to cylinder!")));
			break;
		}
	}

}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 1);
	}
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
}

void AInGamePlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (GetPawn())
	{
		GetPawn()->AddMovementInput(ForwardVector, MovementVector.Y);
		GetPawn()->AddMovementInput(RightVector, MovementVector.X);
	}

	UE_LOG(LogTemp, Log, TEXT("DOO"));
}

void AInGamePlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>(); // Multiply Mouse Sensitivity

	AddYawInput(LookVector.X);
	AddPitchInput(-LookVector.Y);
}

void AInGamePlayerController::Jump()
{
	if(GetPawn())
	{
		ADPCharacterBase* DpCharacter = Cast<ADPCharacterBase>(GetPawn());
		if(DpCharacter)
		{
			DpCharacter->Jump();
		}
	}
}

void AInGamePlayerController::Dash()
{
	
}

void AInGamePlayerController::Drop()
{
}

void AInGamePlayerController::Interact()
{
}

void AInGamePlayerController::Shoot()
{
}

void AInGamePlayerController::Aim()
{
}
