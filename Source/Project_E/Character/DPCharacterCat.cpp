

#include "Character/DPCharacterCat.h"

#include "GameFramework/CharacterMovementComponent.h"

ADPCharacterCat::ADPCharacterCat()
{
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->MaxWalkSpeed = 355.f;
}
