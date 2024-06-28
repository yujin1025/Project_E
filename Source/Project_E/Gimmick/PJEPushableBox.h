
#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "PJEPushableBox.generated.h"

UCLASS()
class PROJECT_E_API APJEPushableBox : public APJEInteractiveActor
{
	GENERATED_BODY()
	
public:	
	APJEPushableBox();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
