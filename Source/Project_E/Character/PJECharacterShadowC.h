// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterNonPlayer.h"
#include "Character/PJECharacterShadow.h"
#include "AI/Enemies/Interface/PJEBlinkable.h"
#include "AI/Enemies/Interface/PJETeleportable.h"
#include "AI/Enemies/Interface/PJEFieldSpawnable.h"
#include "PJECharacterShadowC.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowC : public APJECharacterShadow, public IPJEBlinkable, public IPJETeleportable, public IPJEFieldSpawnable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float BlinkDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float SingleBlinkDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float TeleportRange;

public:
	APJECharacterShadowC();

	virtual float GetBlinkDuration() override;
	virtual float GetSingleBlinkDuration() override;
	virtual float GetTeleportRange() override;
	
	void BeginPlay();

	float GetAIPatrolRadius();

	float GetAIDetectRange();

	float GetAIAttackRange();

	float GetAITurnSpeed();

	void AttackByAI();

// Battle Section
protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
