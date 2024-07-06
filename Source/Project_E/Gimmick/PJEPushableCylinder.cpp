#include "Gimmick/PJEPushableCylinder.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "PJELockDoor.h"
#include "Character/PJECharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
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
	if(CheckCylinderIsDerailed())
	{
		RegenerateCylinder();
	}
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

void APJEPushableCylinder::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bIsAccelerating);
	DOREPLIFETIME(ThisClass, bIsStopped);
	DOREPLIFETIME(ThisClass, bIsForward);
}

void APJEPushableCylinder::InteractionKeyPressed_Implementation(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);
	
	if(!bIsInteractAble || bIsInteracting || !Character) return;

	SetOwner(Character);
	UE_LOG(LogTemp, Log, TEXT("Set Owner"));
	
	Server_InteractionKeyPressed(Character);
	
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

void APJEPushableCylinder::Server_InteractionKeyPressed_Implementation(APJECharacterPlayer* Character)
{
	NetMulticast_InteractionKeyPressed(Character);
}

void APJEPushableCylinder::NetMulticast_InteractionKeyPressed_Implementation(APJECharacterPlayer* Character)
{
	bIsInteracting = true;

	UE_LOG(LogTemp, Warning, TEXT("Set Owner Character"));

	OwnerCharacter = Character;
	
	// Set Forward Vector
	FVector PawnLocation = Character->GetActorLocation();
	FVector CylinderLocation = this->GetActorLocation();
	
	FRotator TargetRotation = (CylinderLocation - PawnLocation).Rotation();
	TargetRotation = FRotator(0.f, TargetRotation.Yaw, 0.f);
	DistanceBetween = FVector(PawnLocation.X - CylinderLocation.X, PawnLocation.Y - CylinderLocation.Y,
		PawnLocation.Z - CylinderLocation.Z);
	float AngleRadian = FQuat(TargetRotation).AngularDistance(FQuat(GetActorRotation()));
	float AngleDegree = FMath::RadiansToDegrees(AngleRadian);

	if(AngleDegree > 90.f)
	{
		TargetRotation = (-1.f * (GetActorRotation().Vector())).Rotation();
		bIsForward = false;
	}
	else
	{
		TargetRotation = GetActorRotation();
		bIsForward = true;
	}

	TempRotation = TargetRotation;
	MovementDirection = TargetRotation;
	
	// Set Character.. 
	Character->SetActorRotation(TargetRotation);
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
		if(MoveSpeed >= 350.f)
		{
			MoveSpeed = 350.f;
		}
	}
	else
	{
		MoveSpeed -= Acceleration * DeltaTime * 4.f;
		if(MoveSpeed <= 0.f)
		{
			MoveSpeed = 0.f;
			bIsStopped = true;
		}
	}

	MoveCylinder(DeltaTime);
	// TODO
	// a. Move cylinder
	// b. Calculate turn rate
	// c. Turn cylinder
	// d. Turn player
}

void APJEPushableCylinder::MoveCylinder(float DeltaTime)
{
	Server_MoveCylinder(DeltaTime);
}

void APJEPushableCylinder::Server_MoveCylinder_Implementation(float DeltaTime)
{
	/** Implementation
	/ a. Movement only applies to cylinder
	/ b. Character is ANCHORED to a cylinder
	/ c. When the cylinder moves, the character moves with it
	/ d. The size of the DeltaVector determines the speed of the pushing animation
	**/
	
	if(!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Owner Character"));		
		return;
	}
	
	
	// Move (Cylinder & Character)
	FVector CurrentLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Movement Direction : %s"), *MovementDirection.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Movement Speed : %f"), MoveSpeed);
	FVector DeltaVector = MovementDirection.Vector() * MoveSpeed * DeltaTime;
	SetActorLocation(CurrentLocation + DeltaVector);

	if(OwnerCharacter && bIsAccelerating)
	{
		FVector RotatedRelativeLocation = (MovementDirection - TempRotation).RotateVector(DistanceBetween);

		FVector NewLocationCharacter = GetActorLocation() + RotatedRelativeLocation;
		OwnerCharacter->SetActorLocation(NewLocationCharacter);
		OwnerCharacter->SetActorRotation(MovementDirection);
	} 

	// R*L Turn (Cylinder & Character)
	if(OwnerCharacter->GetController())
	{
		FRotator ControlRotation = OwnerCharacter->GetController()->GetControlRotation();
		FRotator CurrentForwardRotation = bIsForward ? GetActorRotation() : (-1.f * (GetActorRotation().Vector())).Rotation();
		FRotator CurrentActorRotation = GetActorRotation();
		float ControlRotationYaw = ControlRotation.Yaw;
		
		float RotationDifference = ControlRotationYaw - CurrentForwardRotation.Yaw;
		
		RotationDifference = fmod(RotationDifference, 360.f);
		if(RotationDifference > 90.f)
		{
			RotationDifference -= 180.f;
		}

		UE_LOG(LogTemp, Warning, TEXT("Control Rotation : %f, Actor Rotation : %f"), ControlRotationYaw, CurrentForwardRotation.Yaw);
		UE_LOG(LogTemp, Warning, TEXT("Rotation Differ : %f"), RotationDifference);

		MovementDirection.Yaw += RotationDifference * 0.5f * DeltaTime;
		CurrentActorRotation.Yaw = MovementDirection.Yaw;
		SetActorRotation(CurrentActorRotation);
	}

	// Rotate (Cylinder)
}

void APJEPushableCylinder::NetMulticast_MoveCylinder_Implementation(float DeltaTime)
{
}

bool APJEPushableCylinder::CheckCylinderIsDerailed()
{
	return false;
}

void APJEPushableCylinder::RegenerateCylinder()
{
}

