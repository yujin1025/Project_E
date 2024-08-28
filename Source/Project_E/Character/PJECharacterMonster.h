// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterNonPlayer.h"
#include "PJECharacterMonster.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EMonsterRank : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Elite UMETA(DisplayName = "Elite"),
	Boss UMETA(DisplayName = "Boss")
};

UCLASS()
class PROJECT_E_API APJECharacterMonster : public APJECharacterNonPlayer
{
	GENERATED_BODY()
	
public:
	APJECharacterMonster();

	virtual void BeginPlay() override;

// Component Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UPJEHpBarWidgetComponent> HealthBarComponent;

// Destory Section
public:
	void OnDeath();

protected:
	void DelayedDestroy();
	FTimerHandle DestructionTimer;
	
// Stat Section
public:
	FORCEINLINE void SetCurrentHP(int32 CurrentHp);
	FORCEINLINE int32 GetCurrentHP() const;
	FORCEINLINE float GetMoveSpeed() const;

protected:
	EMonsterRank MonsterRank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaxHp;

	int32 CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MoveSpeed;

// HP Section
/*
public:
	void UpdateHealthBar();

protected:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
*/
};
