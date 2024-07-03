#include "Gimmick/PJEPushableCylinder.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PJELockDoor.h"
#include "Camera/CameraComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
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

	AccelerateCylinder();
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

void APJEPushableCylinder::ReturnPawn()
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
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJEPushableCylinder::Roll);
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &ThisClass::ReturnPawn);
}

void APJEPushableCylinder::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	// TODO
	// c. Pre Interaction -> Setup Input and Interaction variables
	// d. Pre Interaction -> Setup Animation
	
	Super::InteractionKeyPressed(Character);
	
	// Set Forward Vector
	FVector PawnLocation = Character->GetActorLocation();
	FVector CylinderLocation = this->GetActorLocation();
	
	FRotator TargetRotation = (CylinderLocation - PawnLocation).Rotation();
	TargetRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);

	float AngleRadian = FQuat(TargetRotation).AngularDistance(FQuat(GetActorRotation()));
	float AngleDegree = FMath::RadiansToDegrees(AngleRadian);

	if(AngleDegree > 30.f)
	{
		TargetRotation = (-1.f * (GetActorRotation().Vector())).Rotation();
	}
	else
	{
		TargetRotation = GetActorRotation();
	}

	// Set Character.. Very Hard 
	Character->SetActorRotation(TargetRotation);
	//
	// UCameraComponent* Camera = Character->GetCamera();
	USpringArmComponent* CameraBoom = Character->GetCameraBoom();
	CameraBoom->TargetArmLength = 400.f;
	//
	// CameraBoom->SetRelativeRotation(FRotator::ZeroRotator);
	// Camera->SetRelativeLocation(FVector(0.f, 0.f, 80.f));

	
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
	// a. set bIsAccelerating = true
	// b. Do Rotate by calculating the difference between ControlRotation and ActorRotation
}

void APJEPushableCylinder::StopRoll()
{
	// TODO
	// 
}

void APJEPushableCylinder::AccelerateCylinder()
{
	if(bIsAccelerating)
	{
		// Accelerating
	}
	else
	{
		// Decelerating
	}
}

bool APJEPushableCylinder::CheckCylinderIsDerailed()
{
	return false;
}

void APJEPushableCylinder::RegenerateCylinder()
{
}

