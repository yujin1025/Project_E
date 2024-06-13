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
class UInventoryWidget;

struct FInputActionValue;

UCLASS()
class PROJECT_E_API APJECharacterPlayer : public APJECharacterBase/*, public IABCharacterHUDInterface*/, public IPJECharacterItemInterface
{
	GENERATED_BODY()

public:
	APJECharacterPlayer();
	
	bool GetItem(int32 ItemCode);
	FORCEINLINE int32 GetHandItemCode() const { return HandItemCode; }
	// INLINE Function for test.. to be Deleted
	FORCEINLINE void SetHandItemCode(int32 ItemCode) { HandItemCode = ItemCode; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetDead() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION() void OnInteractBegin();
	UFUNCTION(Server, Reliable)	void Server_OnInteractBegin();
	UFUNCTION(NetMulticast, Reliable) void Multicast_OnInteractBegin();
	
	UFUNCTION() void OnInteractEnd();
	UFUNCTION(Server, Reliable)	void Server_OnInteractEnd();
	UFUNCTION(NetMulticast, Reliable) void Multicast_OnInteractEnd();

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

	void MoveCameraToTarget(FVector TargetLocation, FRotator TargetRotation);
	void BackCameraToPawn();

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

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* InventoryAction;

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

protected:
	virtual void Landed(const FHitResult& Hit) override;
	void DoubleJump();
	void Dash();
	void StopDash();
	virtual void Grab();
	void OnFalling();

private:
	void OnMove(const FInputActionValue& Value);	
	void OnLook(const FInputActionValue& Value);
	//void OpenInventory();

	bool bIsInventoryOpen = false; 
	UInventoryWidget* InventoryWidgetInstance = nullptr;

 //Item Section
protected:
	//virtual void TakeItem(UItem* Item) override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	//UInventory* Inventory;

	UPROPERTY(EditAnywhere, Category = "UI")
	float PopupDistance;

	UPROPERTY(EditAnywhere)
	int32 HandItemCode = 0;

	UPROPERTY()
	UInventoryWidget* InventoryWidget;
private:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

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




	
	//Test
	FVector OrgLocation;
	FRotator OrgRotation;
};