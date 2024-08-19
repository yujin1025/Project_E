// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadow.h"
#include "AI/Enemies/Interface/PJETeleportable.h"
#include "AI/Enemies/Interface/PJEBlinkable.h"
#include "AI/Enemies/Interface/PJERunAwayable.h"
#include "Sound/SoundCue.h"
#include "PJECharacterShadowA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowA : public APJECharacterShadow, public IPJETeleportable, public IPJEBlinkable, public IPJERunAwayable, public IPJEPlayerDectectable
{
	GENERATED_BODY()
public:
	APJECharacterShadowA();
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

// Stat Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxKeepMovingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BlinkDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float SingleBlinkDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float TeleportRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float RunAwaySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PlayerDetectionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxYDifference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MinYDifference;

public:
	virtual float GetMaxKeepMovingTime() override;
	virtual float GetBlinkDuration() override;
	virtual float GetSingleBlinkDuration() override;
	virtual float GetTeleportRange() override;
	virtual float GetRunAwaySpeed() override;
	virtual float GetPlayerDetectRange() override;
	virtual float GetDetectMaxYDifference() override;
	virtual float GetDetectMinYDifference() override;

// Sound Section
public:
	UPROPERTY()
	TObjectPtr<class APJEShadowArea> ShadowArea;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundCue> LaughSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundAttenuation> LaughAttenuation;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UAudioComponent> LaughAudioComponent;

public:
	void PlaySound();
	void StopSound();

	void SetLaughVolume(float Value);
};
