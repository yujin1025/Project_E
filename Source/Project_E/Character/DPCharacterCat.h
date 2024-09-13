
#pragma once

#include "CoreMinimal.h"
#include "Character/DPCharacterBase.h"
#include "DPCharacterCat.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API ADPCharacterCat : public ADPCharacterBase
{
	GENERATED_BODY()

public:
	ADPCharacterCat();
	void Attack();

protected:
	UFUNCTION(Server, Reliable)
	void Server_Attack();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Attack();
	void ResetAttack();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation")
	UAnimMontage* BrandishMontage;

	FTimerHandle AttackTimerHandle;
	float AttackCooldown = 1.f;
	bool bCanAttack = true;
};
