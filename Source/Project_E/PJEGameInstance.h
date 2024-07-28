#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PJEGameInstance.generated.h"

UCLASS()
class PROJECT_E_API UPJEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void OnStart() override;
	virtual void Shutdown() override;

// Setting Section
protected:
	float CarmeraSpeed;

public:
	void SetCarmeraSpeed(float NewSpeed);
	float GetCarmeraSpeed() const;
};
