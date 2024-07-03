#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "PJEPushableCylinder.generated.h"

struct FInputActionValue;

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

	UFUNCTION()
	void OnLook(const FInputActionValue& Value);
	
	UFUNCTION()
	void Roll();
	
	UFUNCTION()
	void StopRoll();

	void AccelerateCylinder();
	
	bool CheckCylinderIsDerailed(); // 차후 만들 예정

	void RegenerateCylinder();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Cylinder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	class UInputAction* LookAction; // Mouse Axis

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputAction* MoveAction; // W key

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Input")
	UInputAction* InterruptAction; // E key

	FTransform SpawnTransform;
	
	bool bIsAccelerating; // Is cylinder accelerating?

	float MoveSpeed; // Move speed of cylinder
};
