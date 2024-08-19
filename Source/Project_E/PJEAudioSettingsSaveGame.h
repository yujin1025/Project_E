// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PJEAudioSettingsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UAudioSettingsSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
    float MasterVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float BGMVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float EnvironmentVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float SFXVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float NarrationVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    float VoiceChatVolume;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SpeakerMode;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString MicMode;
};