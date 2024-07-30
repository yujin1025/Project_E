// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "PJELockDoor.generated.h"

class APJECharacterPlayer;
class UPJEMovingComponent;

UCLASS()
class PROJECT_E_API APJELockDoor : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	APJELockDoor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;

	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;
	
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_OpenDoor();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_InsertKey();

	bool CheckValidKey(int32 Itemcode);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> KeyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UPJEMovingComponent> MovingComponent;

private:
	UPROPERTY(Replicated)
	bool bIsKeyInserted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "DP_Settings")
	int32 UnlockKeycode = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "DP_Settings")
	int32 DoorNum = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Data")
	class UDataTable* DoorKeyData;
};
