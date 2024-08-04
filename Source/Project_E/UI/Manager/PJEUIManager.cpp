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
        // �ֻ�� UI�� ���̰� ����
        NewTopmostWidget->SetVisibility(ESlateVisibility::Visible);

        // �ٸ� UI�� �Է� ��Ȱ��ȭ
        for (UUserWidget* Widget : PopupWidgets)
        {
            if (Widget && Widget != NewTopmostWidget)
            {
                Widget->SetVisibility(ESlateVisibility::HitTestInvisible);
            }
        }

        // �÷��̾� ��Ʈ�ѷ� ����
        APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->bShowMouseCursor = true;
            PlayerController->SetInputMode(FInputModeUIOnly().SetWidgetToFocus(NewTopmostWidget->TakeWidget()));

            // �ֻ�� ������ Ű���� ��Ŀ���� ����
            NewTopmostWidget->SetKeyboardFocus();
        }

        // �ֻ�� ���� ������Ʈ
        TopmostPopupWidget = NewTopmostWidget;
    }
}

void UPJEUIManager::CloseTopmostPopupWidget(UWorld* WorldContext)
{
    if (TopmostPopupWidget)
    {

        // �ֻ�� ���� ����
        TopmostPopupWidget->RemoveFromParent();
        PopupWidgets.Remove(TopmostPopupWidget);

        TopmostPopupWidget->MarkPendingKill();

        // �ֻ�� ���� ������Ʈ
        TopmostPopupWidget = PopupWidgets.Num() > 0 ? PopupWidgets.Last() : nullptr;

        if (TopmostPopupWidget)
        {
            // �� �ֻ�� ������ ���̰� ����
            ShowTopmostPopupWidget(WorldContext, TopmostPopupWidget);
        }
        else
        {
            // ��� �˾��� ���� ��� �Է� ��� �ʱ�ȭ
            APlayerController* PlayerController = WorldContext->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = false;
                PlayerController->SetInputMode(FInputModeGameOnly());
            }
        }
    }
}