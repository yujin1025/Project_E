// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEIgnitionHandle.generated.h"

class APJERotatingPlatform;
class APJECharacterPlayer;
class UPJERotationPlatform;

UCLASS()
class PROJECT_E_API APJEIgnitionHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEIgnitionHandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPlatformOptions(float Speed, bool bRotate);

	void ResetRotation();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	UPROPERTY(EditAnywhere, Category = "Platform")
	TArray<TObjectPtr<APJERotatingPlatform>> RotationPlatforms;
	
	//For test
	UPROPERTY(EditAnywhere, Category = "Movement")
	int HandleInt = 0;
	int LastHandleInt = 5;

	float PostInputTime = 0;
};
