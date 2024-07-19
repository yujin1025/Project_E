// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadow.h"
#include "AI/Enemies/Interface/PJETeleportable.h"
#include "AI/Enemies/Interface/PJEBlinkable.h"
#include "AI/Enemies/Interface/PJERunAwayable.h"
#include "PJECharacterShadowA.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowA : public APJECharacterShadow, public IPJETeleportable, public IPJEBlinkable, public IPJERunAwayable
{
	GENERATED_BODY()
public:
	APJECharacterShadowA();


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

public:
	virtual float GetMaxKeepMovingTime() override;
	virtual float GetBlinkDuration() override;
	virtual float GetSingleBlinkDuration() override;
	virtual float GetTeleportRange() override;
	virtual float GetRunAwaySpeed() override;


protected:
	virtual void BeginPlay() override;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;


};
