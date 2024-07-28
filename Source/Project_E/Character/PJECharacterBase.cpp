// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Component/HitDeadComponent.h"
#include "../Game/PJEGameModeBase.h"
#include "Component/HealthComponent.h"


// Sets default values
APJECharacterBase::APJECharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	//GetCapsuleComponent()->SetCollisionProfileName();

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	//GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HitDeadComponent = CreateDefaultSubobject<UHitDeadComponent>(TEXT("HitDeadComponent"));

	// TODO : Implement Movement 
	
	// TODO : Implement Attack 

	switch (CharacterType)
	{
	case ECharacterType::Cat:
		CharacterId = 0;
		break;
	case ECharacterType::Duck:
		CharacterId = 1;
		break;
	case ECharacterType::ShadowA:
		CharacterId = 2;
		break;
	case ECharacterType::ShadowB:
		CharacterId = 3;
		break;
	case ECharacterType::ShadowC:
		CharacterId = 4;
		break;
	}
}

// Called when the game starts or when spawned
void APJECharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	// 델리게이트 핸들러 등록
	OnAttackEnd.AddDynamic(this, &APJECharacterBase::OnAttackEndHandler);
}

void APJECharacterBase::SetDead()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	//PlayDeadAnimation();
	SetActorEnableCollision(false);
	//HpBar->SetHiddenInGame(true);
}

// Called every frame
void APJECharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APJECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APJECharacterBase::Move(const FVector2D Value)
{
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Value.Y);
		AddMovementInput(RightDirection, Value.X);
	}
}

void APJECharacterBase::Look(const FVector2D Value)
{
	if (Controller != nullptr)
	{
		AddControllerYawInput(Value.X);
		AddControllerPitchInput(Value.Y);
	}
}

void APJECharacterBase::OnHit()
{
	if (HitDeadComponent)
	{
		HitDeadComponent->PlayHitMontage();
	}
}

void APJECharacterBase::OnDie()
{
	if (HitDeadComponent)
	{
		HitDeadComponent->PlayDeadMontage();
	}
}

bool APJECharacterBase::IsPlayer()
{
	if(Controller)
	{
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 17.f, FColor::Emerald, FString::Printf(TEXT("Player has Controller")));
		return Controller->IsPlayerController();
	}
	return false;
}

FVector APJECharacterBase::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget)
{
	IsFoundTarget = false;
	return FVector::ZeroVector;
}

void APJECharacterBase::OnAttackEndHandler()
{
	bIsAttacking = false;
}

