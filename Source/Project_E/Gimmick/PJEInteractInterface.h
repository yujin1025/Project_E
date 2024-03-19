
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PJEInteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPJEInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_E_API IPJEInteractInterface
{
	GENERATED_BODY()

public:
	virtual void ShowInteractWidget();
	virtual void HideInteractWidget();
};
