// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterBase.h"
#include "Interface/PJECharacterItemInterface.h"
#include "PJECharacterPlayer.generated.h"

class APJEInteractiveActor;
class IPJEInteractInterface;
class UBoxComponent;
class UInputMappingContext;
class UInputAction;
class UInventory;

struct FInputActionValue;

UCLASS()
class PROJECT_E_API APJECharacterPlayer : public APJECharacterBase/*, public IABCharacterHUDInterface*/, public IPJECharacterItemInterface
{
	GENERATED_BODY()

public:
	APJECharacterPlayer();

	FORCEINLINE int32 GetHandItemCode() const { return HandItemCode; }
	// INLINE Function for test.. to be Deleted
	FORCEINLINE void SetHandItemCode(int32 ItemCode) { HandItemCode = ItemCode; }
	void InitInput(UEnhancedInputComponent* EnhancedInputComponent);

	virtual void InitWidget();

protected:
	virtual void BeginPlay() override;
	virtual void SetDead() override;
	
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnInteractBegin();
	UFUNCTION(Server, Reliable)
	void ServerOnInteractBegin();
	
	UFUNCTION() void OnInteractEnd();
	UFUNCTION(Server, Reliable)	void Server_OnInteractEnd();

	APJEInteractiveActor* GetClosestActor();
	
	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere)
	float RaycastTargetLength = 100.0f;

public:
	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance);

	FORCEINLINE UCameraComponent* GetCamera() { return FollowCamera; }
	FORCEINLINE USpringArmComponent* GetCameraBoom() { return CameraBoom; }
	void SetCamLocationRotation(FVector TargetLocation, FRotator TargetRotation);
	void BackCamera();
	

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable)
	void Server_DoubleJump();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DoubleJump();

	UFUNCTION(Server, Reliable)
	void Server_Dash();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Dash();

	UFUNCTION(Server, Reliable)
	void Server_StopDash();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_StopDash();

	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(Replicated, EditAnywhere, Category = "Jump")
	float JumpHeight = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	bool bFirstJump = true;

	UPROPERTY(EditAnywhere)
	bool bIsWalking = true;

	int32 JumpCount = 0;

	bool isShift = false;

	bool bIsFalling = false;
	FVector FallingStartLocation;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> DieMessageWidgetClass;

	UUserWidget* DieMessageWidgetInstance;

	bool bHasShownMessage = false;
	
	// Variables for smooth camera movement
	FVector OriginCamLocation;
	FRotator OriginCamRotation;
	FVector TargetCamLocation;
	FRotator TargetCamRotation;
	float OriginSpringArmLength = 150.f;

protected:
	virtual void Landed(const FHitResult& Hit) override;
	virtual void DoubleJump();
	void Dash();
	void StopDash();
	virtual void DropItem();
	void OnFalling();

private:
	void OnMove(const FInputActionValue& Value);	
	void OnLook(const FInputActionValue& Value);


 //Item Section
protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	float PopupDistance;

	UPROPERTY(EditAnywhere)
	int32 HandItemCode = 0;


//Interact Section
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> InteractionTrigger;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	TObjectPtr<APJEInteractiveActor> InteractableActor = NULL;

public:
	// 현재 상호작용하고있는 Actor, 없다면 NULL
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<AActor> InteractActor = NULL;

//Projectile
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
};