// Fill out your copyright notice in the Description page of Project Settings.


#include "HPBarWidget.h"
#include "../Player/PJEPlayerController.h"
#include "../Game/PJEPlayerState.h"
#include "Components/TextBlock.h"

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPTextBlock")));

    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController)
    {
        APJEPlayerState* PlayerState = PlayerController->GetPlayerState<APJEPlayerState>();
        if (PlayerState)
        {
            PlayerState->OnPlayerHPChanged.AddLambda([this](int id, float amount) -> void
                {
                    if (HPText)
                    {
                        HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / 100"), amount)));
                    }
                });
        }
        else
        {
            if (GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Red, TEXT("PlayerState is null!"));
        }
    }
    else
    {
        if (GEngine) GEngine->AddOnScreenDebugMessage(7, 10.f, FColor::Red, TEXT("PlayerController is null!"));
    }
}
