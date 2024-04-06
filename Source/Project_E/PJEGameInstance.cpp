// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEGameInstance.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"

void UPJEGameInstance::Shutdown()
{
    UPJEShadowGeneratorManager::GetInstance()->ShutdownInstance();

    // 기본 Shutdown 처리 호출
    Super::Shutdown();
}
