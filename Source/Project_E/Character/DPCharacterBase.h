
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
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Tick(float DeltaTime) override;
	
	virtual void Jump() override;
	virtual void Dash(bool bDash);
	virtual void Interact(bool bBeginInteract);

protected:
	virtual void BeginPlay() override;
	
	virtual void Landed(const FHitResult& Hit) override;
	void FindClosestInteractiveActor();
	void MarkWidget();

	// Multiplayer Function
	UFUNCTION(Server, Reliable)
	void Server_Dash(bool bDash);

private:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Camera")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Camera")
	UCameraComponent* Camera;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Player")
	ECharacterType CharacterType;

	// Variables
	float Speed;
	uint8 JumpCount = 0;
	float JumpHeight = 500.f;
	UPROPERTY(Replicated)
	bool bIsDash;
	
public:
	// Getter & Setters
	FORCEINLINE float GetSpeed() const { return Speed; }
	FORCEINLINE void SetSpeed(const float NewSpeed) { Speed = NewSpeed; }
	FORCEINLINE void SetJumpHeight(const float NewJumpHeight) { JumpHeight = NewJumpHeight; }
	FORCEINLINE void SetCharacterType(const ECharacterType NewCharacterType) { CharacterType = NewCharacterType; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }
};
