// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEGameInstance.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"
#include "Blueprint/UserWidget.h"

void UPJEGameInstance::OnStart()
{
	Super::OnStart();
	/*
	// SettingsMenuClass�� �����Ǿ� �ִ��� Ȯ��
	if (SettingsMenuClass)
	{
		SettingsMenu = CreateWidget<UUserWidget>(this, SettingsMenuClass);
		if (SettingsMenu)
		{
			// ������ ȭ�鿡 �߰��ϰ� ǥ��
			SettingsMenu->AddToViewport();
			SettingsMenu->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SettingsMenu could not be created."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SettingsMenuClass is not set."));
	}
	*/
}

void UPJEGameInstance::Shutdown()
{
    Super::Shutdown();
	/*
	if (SettingsMenu)
	{
		SettingsMenu->RemoveFromViewport();
		SettingsMenu = nullptr;
	}
	*/
}
