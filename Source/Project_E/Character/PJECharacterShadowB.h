// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterShadowA.h"
#include "AI/Enemies/Interface/PJEFieldSpawnable.h"
#include "AI/Enemies/Interface/PJEChasable.h"
#include "PJECharacterShadowB.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterShadowB : public APJECharacterShadow, public IPJEFieldSpawnable, public IPJEChasable, public IPJEPlayerDectectable
{
	GENERATED_BODY()
public:
	APJECharacterShadowB();

protected:
	virtual void BeginPlay() override;

// Stat Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ChaseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PlayerDetectionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MaxYDifference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MinYDifference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FieldRadius = 160.0f; // 1.6m
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FieldDuration = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float DamagePerSecond = 0.1f;

public:
	virtual float GetChaseSpeed() override;
	virtual float GetPlayerDetectRange() override;
	virtual float GetDetectMaxYDifference() override;
	virtual float GetDetectMinYDifference() override;
	virtual float GetFieldRadius() override;
	virtual float GetFieldDuration() override;
	virtual float GetDamagePerSecond() override;

// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void AttackByAI() override;

// Battle Section
protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
