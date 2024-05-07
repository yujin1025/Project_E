// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/PJEGameInterface.h"
#include "PJEGameModeBase.generated.h"

class UBaseWidget;

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEGameModeBase : public AGameModeBase, public IPJEGameInterface
{
	GENERATED_BODY()

public:
	APJEGameModeBase();

	virtual void BeginPlay() override;
	
	virtual void OnPlayerDead(int PlayerNumber) override;
	
private:
	void OpenWidget();


public:
	UPROPERTY()
	UBaseWidget* InGameWindowWidget;

private:
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UBaseWidget> InGameWindowWidgetClass;
};
