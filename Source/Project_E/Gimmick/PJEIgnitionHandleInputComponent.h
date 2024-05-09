// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PJEIgnitionHandleInputComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UPJEIgnitionHandleInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPJEIgnitionHandleInputComponent();

protected:
	virtual void BeginPlay() override;
	void NotifyState();

public:
	void SetupInputBinding();
	void TurnClockwise();
	void TurnCounterClockwise();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TObjectPtr<APJERotatingPlatform>> RotationPlatforms;
	UPROPERTY(EditAnywhere, Category = "Movement")
	ERotateState CurrentRotateState;
	ERotateState LastRotateState;
	
	
};
