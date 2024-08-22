// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/PJECharacterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"
#include "Gimmick/IgnitionHandle.h"
#include "../UI/BaseWidget.h"
#include "Game/PJEPlayerState.h"
#include "Game/PJEGameState.h"
#include "Gimmick/PJEPushableCylinder.h"
#include "UI/Manager/PJEUIManager.h"


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

	if (HasAuthority())
	{
		OpenWidget();
	}
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

	if(IsLocalController())
	{
		FString PlayerRole;
		if(PlayerState)
		{
			PlayerRole = (Cast<APJEPlayerState>(PlayerState)->GetPlayerRole() == EPlayerRole::Cat) ? TEXT("Cat") : TEXT("Duck");
		}
		if(GEngine) GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Emerald, FString::Printf(TEXT("InGamePlayerController / PlayerRole : %s"), *PlayerRole));
	}

	if(IsLocalController())
	{
		ENetMode NetMode = GetNetMode();
		switch (NetMode)
		{
		case NM_Standalone:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : Standalone")));
			break;
		case NM_ListenServer:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : ListenServer")));
			break;
		case NM_Client:
			if(GEngine) GEngine->AddOnScreenDebugMessage(4, 1.f, FColor::Black, FString::Printf(TEXT("NetMode : Client")));
			break;
		}
	}
}

void APJEPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ToggleSettingsMenuAction, ETriggerEvent::Triggered, this, &APJEPlayerController::ToggleSettingsMenu);
	}
}

void APJEPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (PlayerState)
	{
		if (GetPawn())
		{
			Client_Init();
		}
		else
		{
			GetWorld()->GetTimerManager().SetTimerForNextTick(this, &APJEPlayerController::TryClientInit);
		}
	}
}

void APJEPlayerController::TryClientInit()
{
	if (GetPawn())
	{
		Client_Init();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &APJEPlayerController::TryClientInit);
	}
}

// Input Switch Function

void APJEPlayerController::InitInputPawn()
{
	PlayerPawn = GetPawn();
	
	ControllerOperation = EControllerOperation::ECO_Pawn;
	
	APawn* PossessedPawn = GetPawn();
	if(!PossessedPawn) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultContext, 0);
		Subsystem->AddMappingContext(SettingContext, 1);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionBindings();
		APJECharacterPlayer* CharacterPlayer = Cast<APJECharacterPlayer>(PossessedPawn);
		CharacterPlayer->InitInput(EnhancedInputComponent);
	}

	EnhancedInputComponent->BindAction(ToggleSettingsMenuAction, ETriggerEvent::Started, this, &APJEPlayerController::ToggleSettingsMenu);
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
	ControllerOperation = EControllerOperation::ECO_Roll;

	if(!OperatingActor) return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(CylinderContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->ClearActionBindings();
		APJEPushableCylinder* Cylinder = Cast<APJEPushableCylinder>(OperatingActor);
		Cylinder->InitInput(EnhancedInputComponent);
	}
}

// End Input Switch Function


void APJEPlayerController::GameOver()
{
}


APJEPlayerState* APJEPlayerController::GetState()
{
	return Cast<APJEPlayerState>(PlayerState);
}

void APJEPlayerController::Client_Init_Implementation()
{
	InitInputPawn();

	PlayerPawn = GetPawn();
	if (!PlayerPawn)
		return;

	APJECharacterPlayer* CharacterPlayer = Cast<APJECharacterPlayer>(PlayerPawn);
	if (CharacterPlayer)
	{
		CharacterPlayer->InitWidget();
		OpenWidget();
	}
}


void APJEPlayerController::OpenWidget()
{
	InGameWindowWidget = CreateWidget<UBaseWidget>(GetWorld(), InGameWindowWidgetClass);
	if (InGameWindowWidget != nullptr)
	{
		InGameWindowWidget->AddToViewport(1);
	}
}

void APJEPlayerController::ToggleSettingsMenu(const FInputActionValue& Value)
{
	if (SettingsMenuClass)
	{
		if (!SettingsMenu.IsValid() || SettingsMenu->IsPendingKill())
		{
			if (UPJEUIManager::GetInstance()->GetTopmostPopupWidget() == nullptr)
			{
				SettingsMenu = UPJEUIManager::GetInstance()->ShowPopupUI(GetWorld(), SettingsMenuClass);
			}
			
		}
	}
}