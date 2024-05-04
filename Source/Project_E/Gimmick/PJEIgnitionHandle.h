// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEIgnitionHandle.generated.h"

enum class ERotateState : uint8;
class APJERotatingPlatform;
class APJECharacterPlayer;
class UPJERotationPlatform;

UCLASS()
class PROJECT_E_API APJEIgnitionHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	APJEIgnitionHandle();

protected:
	virtual void BeginPlay() override;

	void NotifyState(ERotateState RotateState);

public:	
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TObjectPtr<APJERotatingPlatform>> RotationPlatforms;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	ERotateState CurrentRotateState;
	ERotateState LastRotateState;
	
	float TimeAfterInput;
	float DelayTime;
};
