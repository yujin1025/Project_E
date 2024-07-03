#include "Gimmick/PJEPushableCylinder.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PJELockDoor.h"
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

	AccelerateCylinder(DeltaTime);
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
			Cast<APJECharacterPlayer>(LocalPlayerController->GetPawn())->GetCameraBoom()->TargetArmLength = 150.f;
		}
	}
}

void APJEPushableCylinder::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APJEPushableCylinder::Roll);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APJEPushableCylinder::StopRoll);
	EnhancedInputComponent->BindAction(InterruptAction, ETriggerEvent::Completed, this, &ThisClass::ReturnPawn);
}

void APJEPushableCylinder::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	// TODO
	// c. Pre Interaction -> Setup Input and Interaction variables
	// d. Pre Interaction -> Setup Animation
	
	Super::InteractionKeyPressed(Character);

	OwnerCharacter = Character;
	
	// Set Forward Vector
	FVector PawnLocation = Character->GetActorLocation();
	FVector CylinderLocation = this->GetActorLocation();
	
	FRotator TargetRotation = (CylinderLocation - PawnLocation).Rotation();
	TargetRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);
	MovementDirection = TargetRotation;
	
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

	// Setup Input

	APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(Character->GetController());

	if(LocalPlayerController)
	{
		LocalPlayerController->SetOperatingActor(this);
		LocalPlayerController->InitInputRoll();
	}
	
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
	bIsStopped = false;
	bIsAccelerating = true;
}

void APJEPushableCylinder::StopRoll()
{
	bIsAccelerating = false;
}

void APJEPushableCylinder::AccelerateCylinder(float DeltaTime)
{
	if(bIsStopped) return;
	
	if(bIsAccelerating)
	{
		MoveSpeed += Acceleration * DeltaTime;
		
	}
	else
	{
		MoveSpeed -= Acceleration * DeltaTime * 2.f;
		if(MoveSpeed <= 0.f)
		{
			MoveSpeed = 0.f;
			bIsStopped = true;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("Current Speed is : %f"), MoveSpeed);

	MoveCylinder(DeltaTime);
	// TODO
	// a. Move cylinder
	// b. Calculate turn rate
	// c. Turn cylinder
	// d. Turn player
}

void APJEPushableCylinder::MoveCylinder(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + MovementDirection.Vector() * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	if(OwnerCharacter && bIsAccelerating)
	{
		OwnerCharacter->AddMovementInput(MovementDirection.Vector(), MoveSpeed*DeltaTime);
	}
}

bool APJEPushableCylinder::CheckCylinderIsDerailed()
{
	return false;
}

void APJEPushableCylinder::RegenerateCylinder()
{
}

