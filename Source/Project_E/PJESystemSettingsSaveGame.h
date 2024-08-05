// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PJESystemSettingsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UPJESystemSettingsSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = "Settings")
    FString Resolution;

    UPROPERTY(VisibleAnywhere, Category = "Settings")
    FString ScreenMode;

    UPROPERTY(VisibleAnywhere, Category = "Settings")
    float CameraSpeed;

    UPROPERTY(VisibleAnywhere, Category = "Settings")
    float Brightness;
};