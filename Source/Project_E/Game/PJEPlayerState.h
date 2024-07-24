// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PJEPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Cat UMETA(DisplayName = "고양이"),
	Duck UMETA(DisplayName = "오리"),
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, float)
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	APJEPlayerState();

	FOnHPChangedDelegate OnPlayerHPChanged;
	
	void OnChangePlayerHealth(int objectId, float Amount);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void SeamlessTravelTo(APlayerState* NewPlayerState) override;
	
	virtual void CopyProperties(APlayerState* PlayerState) override;
	
private:
	UPROPERTY(Replicated)
	EPlayerRole PlayerRole;

public:
	FORCEINLINE void SetPlayerRole(EPlayerRole NewPlayerRole) { PlayerRole = NewPlayerRole; }
	FORCEINLINE EPlayerRole GetPlayerRole() { return PlayerRole; }
};
