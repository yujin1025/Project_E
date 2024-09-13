// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/InGamePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/DPCharacterBase.h"
#include "Character/DPCharacterCat.h"
#include "Character/DPCharacterDuck.h"

void AInGamePlayerController::Client_SwitchInput_Implementation(EInputType NewInputType)
{
	if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		InputType = NewInputType;
		switch (NewInputType)
		{
		case EInputType::IT_Player:
			Subsystem->AddMappingContext(PlayerContext, 1);
			InitPlayerInput();
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Change input to player!")));
			break;
		case EInputType::IT_Handle:
			Subsystem->AddMappingContext(HandleContext, 1);
			InitHandleInput();
			if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Change input to handle!")));
			break;
		case EInputType::IT_Cylinder:
			Subsystem->AddMappingContext(CylinderContext, 1);
			InitCylinderInput();
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

	InitPlayerInput();
}

void AInGamePlayerController::InitPlayerInput()
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->ClearActionBindings();
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ThisClass::Dash, true);
	EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &ThisClass::Dash, false);
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ThisClass::Attack);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::Interact);
}

void AInGamePlayerController::InitHandleInput()
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->ClearActionBindings();
	
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Started, this, &ThisClass::Interact);
}

void AInGamePlayerController::InitCylinderInput()
{
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->ClearActionBindings();
	
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Started, this, &ThisClass::Interact);
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
}

void AInGamePlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>(); // Multiply Mouse Sensitivity

	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void AInGamePlayerController::Jump()
{
	if(GetPawn())
	{
		ADPCharacterBase* DpCharacter = Cast<ADPCharacterBase>(GetPawn());
		if(DpCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("Jump"));
			DpCharacter->Jump();
		}
	}
}

void AInGamePlayerController::Dash(const bool bIsDash)
{
	if(GetPawn())
	{
		ADPCharacterBase* DpCharacter = Cast<ADPCharacterBase>(GetPawn());
		if(DpCharacter){
			DpCharacter->Dash(bIsDash);
		}
	}
}

void AInGamePlayerController::Drop()
{
}

void AInGamePlayerController::Interact()
{
	ADPCharacterBase* DpCharacter = Cast<ADPCharacterBase>(GetPawn());
	if(DpCharacter)
	{
		if(InputType == EInputType::IT_Player)
		{
			// Begin Interact
			DpCharacter->Interact(true);
		}
		else
		{
			// End Intereact
			DpCharacter->Interact(false);
		}
	}
}

void AInGamePlayerController::Attack()
{
	// Success Cast to Cat
	if(ADPCharacterCat* Cat = Cast<ADPCharacterCat>(GetPawn()))
	{
		Cat->Attack();
	}
	// Success Cast to Duck
	else if(ADPCharacterDuck* Duck = Cast<ADPCharacterDuck>(GetPawn()))
	{
		// Call duck attack function
	}
}

void AInGamePlayerController::Aim()
{
	if(ADPCharacterDuck* Duck = Cast<ADPCharacterDuck>(GetPawn()))
	{
		// Aim action only execute at duck
	}
}
