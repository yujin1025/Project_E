// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PJECharacterNonPlayer.h"
#include "AI/Enemies/Interface/PJERushable.h"
#include "PJECharacterBoss.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJECharacterBoss : public APJECharacterNonPlayer, public IPJERushable
{
	GENERATED_BODY()
public:
	APJECharacterBoss();

protected:
	virtual void BeginPlay() override;

// Stat Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float RushSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float RushDistance;

public:
	virtual float GetRushSpeed() override;
	virtual float GetRushDistance() override;

};
