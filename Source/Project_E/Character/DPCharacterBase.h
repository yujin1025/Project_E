
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DPCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
enum class ECharacterType;

UCLASS()
class PROJECT_E_API ADPCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ADPCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;
	virtual void Dash();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_Dash();
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Dash();
	
	virtual void Landed(const FHitResult& Hit) override;

private:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Camera")
	UCameraComponent* Camera;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Player")
	ECharacterType CharacterType;

	// Variables
	uint8 JumpCount = 0;
	float JumpHeight = 500.f;

public:
	FORCEINLINE void SetJumpHeight(const float NewJumpHeight) { JumpHeight = NewJumpHeight; }
	FORCEINLINE void SetCharacterType(const ECharacterType NewCharacterType) { CharacterType = NewCharacterType; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }
};
