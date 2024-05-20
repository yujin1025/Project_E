// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PJERotateComponent.generated.h"


UENUM(BlueprintType)
enum class ERotateState : uint8
{
	Interrupt UMETA(DisplayName = "정지"),
	Rotating UMETA(DisplayName = "회전"),
	Returning UMETA(DisplayName = "복귀"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UPJERotateComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UPJERotateComponent();

protected:
	void OperateRotation(float DeltaTime);
	void StopRotation();
	void ResetRotation(float DeltaTime);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator OriginRotation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FRotator RotationAngle;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxRotateDegree;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 0.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	ERotateState RotateState;
	UPROPERTY(EditAnywhere, Category = "Movement")
	TObjectPtr<USceneComponent> RotateTarget;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FORCEINLINE void SetRotationAngle(FRotator NewRotationAngle) { RotationAngle = NewRotationAngle; }
	FORCEINLINE void SetRotationOffset(float NewMaxRotateDegree) { MaxRotateDegree = NewMaxRotateDegree; }
	FORCEINLINE void SetRotationSpeed(float NewRotationSpeed) { RotationSpeed = NewRotationSpeed; }
	FORCEINLINE void SetRotateState(ERotateState NewRotateState) { RotateState = NewRotateState; }
	FORCEINLINE void SetRotateTarget(USceneComponent* NewRotateTarget) {RotateTarget = NewRotateTarget;}
	
	FORCEINLINE FRotator GetRotationAngle() const { return RotationAngle; }
	FORCEINLINE float GetMaxRotateDegree() const { return MaxRotateDegree; }
	FORCEINLINE float GetRotationSpeed() const { return RotationSpeed; }
	FORCEINLINE ERotateState GetRotateState() const { return RotateState; }
	FORCEINLINE USceneComponent* GetRotateTarget() const { return RotateTarget; }

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsMaxRotate = false;

};