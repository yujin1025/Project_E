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

protected:
	EMonsterRank MonsterRank;
	int32 MaxHp;
	int32 CurrentHp;
	float MoveSpeed;

};
