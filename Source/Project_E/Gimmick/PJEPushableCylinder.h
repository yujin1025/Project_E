#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "PJEPushableCylinder.generated.h"

UCLASS()
class PROJECT_E_API APJEPushableCylinder : public APJEInteractiveActor
{
	GENERATED_BODY()
	
public:	
	APJEPushableCylinder();
	
	virtual void Tick(float DeltaTime) override;
	
	void InitInput(UEnhancedInputComponent* EnhancedInputComponent);
	
protected:
	virtual void BeginPlay() override;

	void ReturnPawnInput();

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Cylinder;

	class UPJERotateComponent* RotateComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	class UInputAction* LookAction; // Mouse Axis

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputAction* MoveAction; // W key

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputAction* InterruptAction; // E key

	FTransform SpawnTransform;
};
