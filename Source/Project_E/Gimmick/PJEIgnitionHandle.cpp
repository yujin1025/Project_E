#include "PJEIgnitionHandle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PJECamPos.h"
#include "PJERotateComponent.h"

#include "PJERotatingPlatform.h"
#include "ShaderPrintParameters.h"
#include "Character/PJECharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/PJEPlayerController.h"

APJEIgnitionHandle::APJEIgnitionHandle()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Create SubObject **/
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	SetRootComponent(BaseMesh);
	BaseMesh->SetGenerateOverlapEvents(false);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	Widget->SetupAttachment(BaseMesh);

	InteractTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	InteractTrigger->SetupAttachment(BaseMesh);

	/* Enhanced Input **/
	HandleContext = LoadObject<UInputMappingContext>(nullptr, TEXT("/Game/Input/Gimmick/IgnitionHandle/IMC_IgnitionHandle"));
	TurnAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/Gimmick/IgnitionHandle/IA_Turn"));
	InterruptAction = LoadObject<UInputAction>(nullptr, TEXT("/Game/Input/Gimmick/IgnitionHandle/IA_Interrupt"));
}

void APJEIgnitionHandle::BeginPlay()
{
	Super::BeginPlay();

	Widget->SetVisibility(false);
	
	LastRotateState = ERotateState::Interrupt;
	CurrentRotateState = ERotateState::Interrupt;
}

void APJEIgnitionHandle::NotifyState(ERotateState RotateState, float Speed)
{
	for(auto RotationPlatform: RotationPlatforms)
	{
		UPJERotateComponent* RotateComponent = RotationPlatform->GetRotationComponent();
		RotateComponent->SetRotateState(RotateState);
		RotateComponent->SetRotationSpeed(Speed);
	}
}


/* Interact Section **/

// ** BEGIN INTERACT **
void APJEIgnitionHandle::EndInteracting(const AActor* InteractActor)
{
	IPJEInteractInterface::EndInteracting(InteractActor);
	// Prevent duplicate controls
	if(bIsInteract)
	{
		return;
	}
	bIsInteract = true;
	
	AActor* CCInteractActor = const_cast<AActor*>(InteractActor);
	APJECharacterPlayer* InteractCharacter = Cast<APJECharacterPlayer>(CCInteractActor);

	if(IsValid(InteractCharacter))
	{
		// EndInteracting -> SetupInputBinding 순서
		InteractCharacter->InteractActor = this;
		InteractCharacter->MoveCameraToTarget(Campos->GetArrowLocation(), Campos->GetArrowRotation());
	}
}


// ** END INTERACT **
void APJEIgnitionHandle::ReturnPawn()
{
	if(CurrentPossessingController == NULL)
	{
		UE_LOG(LogTemp,Warning, TEXT("There is No Possesing Controller"))
		return;
	}
	APJECharacterPlayer* MyPlayer = Cast<APJECharacterPlayer>(CurrentPossessingController->GetPlayerPawn());
	CurrentPossessingController = NULL;
	if(MyPlayer)
	{
		if(UInputComponent* PlayerInputComponent = MyPlayer->InputComponent)
		{
			PlayerInputComponent->ClearActionBindings();
		}
		MyPlayer->InteractActor = NULL;
		MyPlayer->BackCameraToPawn();
	}
	
	bIsInteract = false;
}

void APJEIgnitionHandle::ShowInteractWidget()
{
	IPJEInteractInterface::ShowInteractWidget();

	Widget->SetVisibility(true);
}

void APJEIgnitionHandle::HideInteractWidget()
{
	IPJEInteractInterface::HideInteractWidget();

	Widget->SetVisibility(false);
}

// void APJEIgnitionHandle::SetupInputBinding(APJEPlayerController* MyPlayerController)
// {
// 	IPJEInputInterface::SetupInputBinding(MyPlayerController);
//
// 	CurrentPossessingController = MyPlayerController;
// 	
// 	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(MyPlayerController->GetLocalPlayer());
// 	if(EnhancedInputSubsystem)
// 	{
// 		EnhancedInputSubsystem->ClearAllMappings();
// 		EnhancedInputSubsystem->AddMappingContext(HandleContext, 0);
// 	}
// 		
// 	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(MyPlayerController->InputComponent);
// 	if(EnhancedInputComponent)
// 	{
// 		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &APJEIgnitionHandle::DoRotation);
// 		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &APJEIgnitionHandle::StopRotation);
// 		EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &APJEIgnitionHandle::ReturnPawn);
// 	}
//
// }

void APJEIgnitionHandle::SetupInputBinding(APJEPlayerController* PlayerController)
{	
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	CurrentPossessingController = PlayerController;
	
	if(EnhancedInputSubsystem)
	{
		EnhancedInputSubsystem->ClearAllMappings();
		EnhancedInputSubsystem->AddMappingContext(HandleContext, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->GetPlayerPawn()->InputComponent);
	if(EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Started, this, &APJEIgnitionHandle::DoRotation);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Completed, this, &APJEIgnitionHandle::StopRotation);
		EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &APJEIgnitionHandle::ReturnPawn);
	}
}

void APJEIgnitionHandle::DoRotation(const FInputActionValue& Value)
{	
	CurrentRotateState = ERotateState::Rotating;

	RotateSpeed = Value.Get<float>() * 10;
}

void APJEIgnitionHandle::StopRotation()
{
	CurrentRotateState = ERotateState::Interrupt;
}

/* End Interact Section **/



void APJEIgnitionHandle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(CurrentRotateState != LastRotateState)
	{
		NotifyState(CurrentRotateState, RotateSpeed);
	}
	LastRotateState = CurrentRotateState;

	if(CurrentRotateState == ERotateState::Rotating)
	{
		TimeAfterInput = 0.f;
	}

	TimeAfterInput += DeltaTime;

	if(TimeAfterInput >= DelayTime)
	{
		CurrentRotateState = ERotateState::Returning;
	}
}
