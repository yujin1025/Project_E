// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEPlatform.generated.h"

UCLASS()
class PROJECT_E_API APJEPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	APJEPlatform();

protected:
	virtual void BeginPlay() override;

private:
	void MovePlatform(float DeltaTime);

	
public:	
	virtual void Tick(float DeltaTime) override;

	void SetbPlatformActive(bool _bPlatformActive) { bPlatformActive = _bPlatformActive; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> PlatformMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement|DP_Settings")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement|DP_Settings")
	float MoveSpeed = 4.f;
	
	float AfterDisactive = 2.f;
	// The time from when the character releases the button until the platform moves into place
	UPROPERTY(EditAnywhere, Category = "Movement|DP_Settings")
	float PlatformDelayTime = 2.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bPlatformActive;

};
