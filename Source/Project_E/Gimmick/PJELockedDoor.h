// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "GameFramework/Actor.h"
#include "PJELockedDoor.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class PROJECT_E_API APJELockedDoor : public AActor, public IPJEInteractInterface
{
	GENERATED_BODY()
	
public:	
	APJELockedDoor();

protected:
	virtual void BeginPlay() override;

	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;

	virtual void BeginInteracting(const AActor* InteractActor) override;
	virtual void EndInteracting(const AActor* InteractActor) override;

	void MoveDoor(float DeltaTime);
	
	bool CheckValidKey(const AActor* InteractActor);
	
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBoxComponent> InteractTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UWidgetComponent> Widget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	int32 UnlockingKeyCode = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	bool bIsUnlocking = false;
	UPROPERTY(VisibleAnywhere, Category="Interaction")
	bool bIsInteractable = false;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime = 0;
};