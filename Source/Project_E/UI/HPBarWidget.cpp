// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Game/PJEGameModeBase.h"
#include "../Game/PJEPlayerState.h"
#include "Components/TextBlock.h"

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPTextBlock")));

	auto* GameMode = Cast<APJEGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode && GameMode->MyPlayerState)
	{
		GameMode->MyPlayerState->OnPlayerHPChanged.AddLambda([this](int id, float amount) -> void
			{
				if (HPText)
				{
					HPText->SetText(FText::FromString(FString::Printf(TEXT("%.1f / 100"), amount)));
				}
			});		
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Something Wrong!"));
	}
}
