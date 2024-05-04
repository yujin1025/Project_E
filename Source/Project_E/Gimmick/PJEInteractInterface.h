
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

	virtual void BeginInteracting(const AActor* InteractActor);
	virtual void EndInteracting(const AActor* InteractActor);
	virtual void BreakInteracting();

	virtual void ShowInteractPointWidget();
	virtual void HideInteracPointWidget();

protected:
	bool bIsInteracting = false;
};
