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

protected:
	virtual void BeginPlay() override;

	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;

	bool CheckValidKey(int32 Itemcode);
	
public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UPJEMovingComponent> MovingComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction|DP_Settings")
	int32 UnlockKeycode = 0;
};
