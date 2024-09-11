

#include "Character/DPCharacterCat.h"

#include "Game/PJEGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"

ADPCharacterCat::ADPCharacterCat()
{
	GetCharacterMovement()->MaxWalkSpeed = 355.f;
	SetJumpHeight(700.f);
	SetCharacterType(ECharacterType::Cat);
}

void ADPCharacterCat::Attack()
{
	// Initial Input
}

void ADPCharacterCat::NetMulticast_Attack_Implementation()
{
	// Attack Logic
}

void ADPCharacterCat::Server_Attack_Implementation()
{
	// Sound & Effect
}
