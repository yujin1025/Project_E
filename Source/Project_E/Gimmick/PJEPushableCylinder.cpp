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

	DOREPLIFETIME(ThisClass, bIsForward);
	DOREPLIFETIME(ThisClass, bIsAccelerating);
	DOREPLIFETIME(ThisClass, bIsStopped);
	DOREPLIFETIME(ThisClass, MoveSpeed);
	DOREPLIFETIME(ThisClass, OwnerCharacter);
}


void APJEPushableCylinder::InteractionKeyPressed_Implementation(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);
	Server_Interaction(Character);
	
	OwnerCharacter = Character;
	
	// Set Forward Vector
	FVector PawnLocation = Character->GetActorLocation();
	FVector CylinderLocation = this->GetActorLocation();
	
	FRotator TargetRotation = (CylinderLocation - PawnLocation).Rotation();
	UE_LOG(LogTemp, Warning, TEXT("Movement Direction : %s"), *TargetRotation.ToString());
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
	USpringArmComponent* CameraBoom = Character->GetCameraBoom();
	CameraBoom->TargetArmLength = 400.f;

	// Setup Input
	APJEPlayerController* LocalPlayerController = Cast<APJEPlayerController>(Character->GetController());
	if(LocalPlayerController)
	{
		LocalPlayerController->SetOperatingActor(this);
		LocalPlayerController->InitInputRoll();
	}
	
}

void APJEPushableCylinder::Server_Interaction_Implementation(APJECharacterPlayer* Character)
{
	NetMulticast_Interaction(Character);	
}

void APJEPushableCylinder::NetMulticast_Interaction_Implementation(APJECharacterPlayer* Character)
{
	SetOwner(OwnerCharacter);
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
}

void APJEPushableCylinder::MoveCylinder(float DeltaTime)
{
	Server_MoveCylinder(DeltaTime);
}

void APJEPushableCylinder::Server_MoveCylinder_Implementation(float DeltaTime)
{
	NetMulticast_MoveCylinder(DeltaTime);
}

void APJEPushableCylinder::NetMulticast_MoveCylinder_Implementation(float DeltaTime)
{
	/** Implementation
	/ a. Movement only applies to cylinder
	/ b. Character is ANCHORED to a cylinder
	/ c. When the cylinder moves, the character moves with it
	/ d. The size of the DeltaVector determines the speed of the pushing animation
	**/
	if(!OwnerCharacter)
	{
		if(HasAuthority())
		{
			UE_LOG(LogTemp, Error, TEXT("Server no OwnerCharacter"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Client no OwnerCharacter"));
		}
		return;
	}
	// Move (Cylinder & Character)
	FVector CurrentLocation = GetActorLocation();
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

		MovementDirection.Yaw += RotationDifference * 0.5f * DeltaTime;
		CurrentActorRotation.Yaw = MovementDirection.Yaw;
		SetActorRotation(CurrentActorRotation);
	}
	
	// Rotate (Cylinder)
	float Radius = 100.f;
	float Pi = 3.14f;
	// Roll이라고 치자
	float DeltaAngle = DeltaVector.Size() / (2 * Radius * Pi) * 360;
	UE_LOG(LogTemp, Warning, TEXT("Forward : %d"), bIsForward);
	DeltaAngle = bIsForward ? -1.f * DeltaAngle : DeltaAngle;
	Cylinder->AddLocalRotation(FRotator(0.f, DeltaAngle, 0.f));
}

bool APJEPushableCylinder::CheckCylinderIsDerailed()
{
	return false;
}

void APJEPushableCylinder::RegenerateCylinder()
{
}

