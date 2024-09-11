
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

protected:
	void Attack();
	UFUNCTION(Server, Reliable)
	void Server_Attack();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Attack();
};
