// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Manager/PJEUIManager.h"
#include "UI/PopUpWidget.h"
#include "GameFramework/PlayerController.h"
#include <Kismet/GameplayStatics.h>

UPJEUIManager* UPJEUIManager::Instance = nullptr;

UPJEUIManager* UPJEUIManager::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = NewObject<UPJEUIManager>();
        Instance->AddToRoot();
    }
    return Instance;
}

UPopUpWidget* UPJEUIManager::ShowPopupUI(UWorld* WorldContext, TSubclassOf<UPopUpWidget> WidgetClass)
{
    if (WidgetClass)
    {
        if (WorldContext)
        {
            UPopUpWidget* NewWidget = CreateWidget<UPopUpWidget>(WorldContext, WidgetClass);
            if (NewWidget)
            {
                NewWidget->AddToViewport();

                AddPopupWidget(NewWidget);
                ShowTopmostPopupWidget(WorldContext, NewWidget);

                return NewWidget;
            }
        }
    }
    return nullptr;
}

void UPJEUIManager::AddPopupWidget(UPopUpWidget* NewWidget)
{
    if (NewWidget && !PopupWidgets.Contains(NewWidget))
    {
        PopupWidgets.Add(NewWidget);
    }
}
void UPJEUIManager::RemovePopupWidget(UWorld* WorldContext, UPopUpWidget* WidgetToRemove)
{
    if (WidgetToRemove)
    {
        PopupWidgets.Remove(WidgetToRemove);

        WidgetToRemove->MarkPendingKill();

        if (WidgetToRemove == TopmostPopupWidget)
        {
            TopmostPopupWidget = PopupWidgets.Num() > 0 ? PopupWidgets.Last() : nullptr;
            if (TopmostPopupWidget)
            {
                ShowTopmostPopupWidget(WorldContext, TopmostPopupWidget);
            }
            else
            {
                APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
                if (PlayerController)
                {
                    PlayerController->bShowMouseCursor = false;
                    PlayerController->SetInputMode(FInputModeGameOnly());
                }
            }
        }

        WidgetToRemove->RemoveFromParent();
    }
}


UPopUpWidget* UPJEUIManager::GetTopmostPopupWidget() const
{
    return TopmostPopupWidget;
}

void UPJEUIManager::ShowTopmostPopupWidget(UWorld* WorldContext, UPopUpWidget* NewTopmostWidget)
{
    if (NewTopmostWidget)
    {
        // 최상단 UI를 보이게 설정
        NewTopmostWidget->SetVisibility(ESlateVisibility::Visible);

        // 다른 UI를 입력 비활성화
        for (UUserWidget* Widget : PopupWidgets)
        {
            if (Widget && Widget != NewTopmostWidget)
            {
                Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
            }
        }

        // 플레이어 컨트롤러 설정
        APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;
            PlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(NewTopmostWidget->TakeWidget()));

            // 최상단 위젯에 키보드 포커스를 설정
            NewTopmostWidget->SetKeyboardFocus();
        }

        // 최상단 위젯 업데이트
        TopmostPopupWidget = NewTopmostWidget;
    }
}

void UPJEUIManager::CloseTopmostPopupWidget(UWorld* WorldContext)
{
    if (TopmostPopupWidget)
    {

        // 최상단 위젯 제거
        TopmostPopupWidget->RemoveFromParent();
        PopupWidgets.Remove(TopmostPopupWidget);

        TopmostPopupWidget->MarkPendingKill();

        // 최상단 위젯 업데이트
        TopmostPopupWidget = PopupWidgets.Num() > 0 ? PopupWidgets.Last() : nullptr;

        if (TopmostPopupWidget)
        {
            // 새 최상단 위젯을 보이게 설정
            ShowTopmostPopupWidget(WorldContext, TopmostPopupWidget);
        }
        else
        {
            // 모든 팝업이 닫힌 경우 입력 모드 초기화
            APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = false;
                PlayerController->SetInputMode(FInputModeGameOnly());
            }
        }
    }
}