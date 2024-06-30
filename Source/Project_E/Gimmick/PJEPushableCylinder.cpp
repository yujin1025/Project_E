#include "Gimmick/PJEPushableCylinder.h"

#include "InputActionValue.h"
#include "PJELockDoor.h"
#include "Player/PJEPlayerController.h"

APJEPushableCylinder::APJEPushableCylinder()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractType = EInteractType::Control;

	Cylinder = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	Cylinder->SetGenerateOverlapEvents(false);
	Cylinder->SetupAttachment(Root);
}

void APJEPushableCylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO
	// a. Do acceleration when isAcceleration is true and calculate current speed
	// b. Scales Actor rotation speed proportional to speed
	// c. If the cylinder derails from the road, regenerate it at the starting position
}

void APJEPushableCylinder::BeginPlay()
{
	Super::BeginPlay();

	SpawnTransform = this->GetTransform();
}

void APJEPushableCylinder::ReturnPawnInput()
{
	bIsInteracting = false;

	UWorld* World = GetWorld();
	if(World)
	{
		APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(World->GetFirstPlayerController());
		if(LocalPlayerController)
		{
			LocalPlayerController->SetOperatingActor(nullptr);
			LocalPlayerController->InitInputPawn();
		}
	}
}

void APJEPushableCylinder::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	
}

void APJEPushableCylinder::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);

	// TODO
	// a. Get Forward Vector and Manipulate it to Move Vector (Roll Forward? Roll Backward?)
	// b. if Move Vector is Valid -> Start Interaction
	// c. Pre Interaction -> Setup Input and Interaction variables
	// d. Pre Interaction -> Setup Animation
}

void APJEPushableCylinder::OnLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	UWorld* World = GetWorld();
	if(World)
	{
		APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(World->GetFirstPlayerController());
		if(LocalPlayerController)
		{
			LocalPlayerController->GetPawn()->AddControllerYawInput(LookAxisVector.X);
			LocalPlayerController->GetPawn()->AddControllerPitchInput(LookAxisVector.Y);						
		}
	}
}

void APJEPushableCylinder::Roll()
{
	// TODO
	// a. set isAcceleration = true
	// b. Do Rotate by calculating the difference between ControlRotation and ActorRotation
}

void APJEPushableCylinder::StopRoll()
{
	// TODO
	// 
}

