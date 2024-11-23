

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
	if(!bCanAttack) return;
	
	if(bCanAttack)
	{
		bCanAttack = false;
		GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::ResetAttack, AttackCooldown);
		Server_Attack();
	}
}

void ADPCharacterCat::Server_Attack_Implementation()
{
	// Server Attack Logic
	NetMulticast_Attack();
}

void ADPCharacterCat::NetMulticast_Attack_Implementation()
{
	// Sound & Effect
	UAnimInstance* CatAnimInstance = GetMesh()->GetAnimInstance();

	if(BrandishMontage)
	{
		CatAnimInstance->Montage_Play(BrandishMontage);
	}
}

void ADPCharacterCat::ResetAttack()
{
	bCanAttack = true;
}