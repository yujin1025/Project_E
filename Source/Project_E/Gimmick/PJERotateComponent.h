// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PJERotateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UPJERotateComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UPJERotateComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator RotationOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsRotating = true;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FORCEINLINE void SetRotationOffset(const FRotator rotationVector) { RotationOffset = rotationVector; }
	FORCEINLINE void SetRotationSpeed(const float rotationSpeed) { RotationSpeed = rotationSpeed; }
	FORCEINLINE void SetIsRotating(const bool isRotating) { bIsRotating = isRotating; }
};