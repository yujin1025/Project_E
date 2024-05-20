
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PJEMovingComponent.generated.h"

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Interrupt UMETA(DisplayName = "정지"),
	Moving UMETA(DisplayName = "이동"),
	Returning UMETA(DisplayName = "복귀"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UPJEMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPJEMovingComponent();

protected:
	virtual void BeginPlay() override;

	void OperateMove(float DeltaTime);
	void StopMove();
	void ResetMove(float DeltaTime);

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement|DP_Settings")
	FVector MovementOffset;
	UPROPERTY(EditAnywhere, Category = "Movement|DP_Settings")
	float MovementSpeed;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	EMovementState MovementState;
	UPROPERTY(EditAnywhere, Category = "Movement")
	TObjectPtr<USceneComponent> MovementTarget;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetMovementOffset(FVector NewTargetLocation) { MovementOffset = NewTargetLocation; }
	FORCEINLINE void SetMovementSpeed(float NewMovementSpeed) { MovementSpeed = NewMovementSpeed; }
	FORCEINLINE void SetMovementState(EMovementState NewMovementState) { MovementState = NewMovementState; }
	FORCEINLINE void SetMovementTarget(USceneComponent* NewMovementTarget) { MovementTarget = NewMovementTarget; }

	FORCEINLINE FVector GetMovementOffset() { return MovementOffset; }
	FORCEINLINE float GetMovementSpeed() { return MovementSpeed; }
	FORCEINLINE EMovementState GetMovementState() { return MovementState; }
	FORCEINLINE USceneComponent* GetMovementTarget() { return MovementTarget; }

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsArrived = false;
		
};
