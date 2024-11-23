// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/PJEGameInterface.h"
#include "Engine/DataTable.h"
#include "PJEGameModeBase.generated.h"

class APJEGameState;
class APJEPlayerState;
class APJEPlayerController;

/**
 * 
 */

UENUM()
enum class ECharacterType
{
	Cat = 0,
	Duck = 1,
	ShadowA = 2,
	ShadowB = 3,
	ShadowC = 4,
	Max,
};

USTRUCT(BlueprintType)
struct FCharacterStatData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FCharacterStatData() : MaxHp(100.0f), MoveSpeed(2.0f) {}

	UPROPERTY(EditAnywhere)
	float MaxHp;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;
};

UCLASS()
class PROJECT_E_API APJEGameModeBase : public AGameModeBase, public IPJEGameInterface
{
	GENERATED_BODY()

public:
	APJEGameModeBase();

	virtual void BeginPlay() override;
	
	virtual void OnPlayerDead(int PlayerNumber) override;
	

public:
	UPROPERTY()
	APJEGameState* MyGameState;

	UPROPERTY()
	APJEPlayerState* MyPlayerState;

protected:
	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	void OnPostLogin(APJEPlayerController* NewPlayer);

private:
	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* CharacterStatTable;

public:
	FCharacterStatData* GetCharacterStat(ECharacterType type);

};
