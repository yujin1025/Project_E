// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/PJECharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Gimmick/IgnitionHandle.h"
#include "../UI/BaseWidget.h"


APJEPlayerController::APJEPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APJEPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 멀티 서버 선택에 따라 캐릭터 달라진다 (PlayerStart)
	PlayerPawn = GetPawn();
	
	InitInputPawn();
	OpenWidget();
}

void APJEPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if(PlayerController)
	{
		APawn* PossessPawn = PlayerController->GetPawn();
		if(!PossessPawn)
		{
			PlayerController->Possess(PlayerPawn);
		}
	}
}


// Input Switch Function

void APJEPlayerController::InitInputPawn()
{
	ControllerOperation = EControllerOperation::ECO_Pawn;
	
	APawn* PossessedPawn = GetPawn();
	if(!PossessedPawn) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionBindings();
		APJECharacterPlayer* CharacterPlayer = Cast<APJECharacterPlayer>(PossessedPawn);
		CharacterPlayer->InitInput(EnhancedInputComponent);
	}
}

void APJEPlayerController::InitInputIgnitionHandle()
{	
	ControllerOperation = EControllerOperation::ECO_IgnitionHandle;

	if(!OperatingActor) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(IgnitionHandleContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionBindings();
		AIgnitionHandle* IgnitionHandle = Cast<AIgnitionHandle>(OperatingActor);
		IgnitionHandle->InitInput(EnhancedInputComponent);
	}
}

void APJEPlayerController::InitInputPush()
{
}

void APJEPlayerController::InitInputRoll()
{
}

// End Input Switch Function


void APJEPlayerController::GameOver()
{
}

void APJEPlayerController::OpenWidget()
{
	InGameWindowWidget = CreateWidget<UBaseWidget>(GetWorld(), InGameWindowWidgetClass);
	if (InGameWindowWidget != nullptr)
	{
		InGameWindowWidget->AddToViewport(1);
	}
}
