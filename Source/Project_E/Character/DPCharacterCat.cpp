

#include "Character/DPCharacterCat.h"

#include "Game/PJEGameModeBase.h"

ADPCharacterCat::ADPCharacterCat()
{
	SetJumpHeight(700.f);
	SetSpeed(355.f);
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
