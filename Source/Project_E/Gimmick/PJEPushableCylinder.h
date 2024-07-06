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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

	void ReturnPawn();

	UFUNCTION(Client, Reliable)
	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;
	UFUNCTION(Server, Reliable)
	void Server_InteractionKeyPressed(APJECharacterPlayer* Character);
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_InteractionKeyPressed(APJECharacterPlayer* Character);

	UFUNCTION()
	void OnLook(const FInputActionValue& Value);
	
	UFUNCTION()
	void Roll();
	
	UFUNCTION()
	void StopRoll();
	
	void AccelerateCylinder(float DeltaTime);

	void MoveCylinder(float DeltaTime);
	UFUNCTION(Server, Reliable) void Server_MoveCylinder(float DeltaTime);
	UFUNCTION(NetMulticast, Reliable) void NetMulticast_MoveCylinder(float DeltaTime);
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Movement")
	float Acceleration;
	
	FTransform SpawnTransform;
	FRotator MovementDirection;
	FRotator TempRotation;
	FVector DistanceBetween; // Distance between cylinder and character

	UPROPERTY(Replicated)
	bool bIsAccelerating; // Is cylinder accelerating?
	UPROPERTY(Replicated)
	bool bIsStopped; // is cylinder's speed zero?
	UPROPERTY(Replicated)
	bool bIsForward;
	
	float MoveSpeed; // Move speed of cylinder

	APJECharacterPlayer* OwnerCharacter;
};
