// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PJEGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJEGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Shutdown() override;
	
};
