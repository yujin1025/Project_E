#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "PJEUIManager.generated.h"

UCLASS()
class PROJECT_E_API UPJEUIManager : public UObject
{
    GENERATED_BODY()

public:
    static UPJEUIManager* GetInstance();

    class UPopUpWidget* ShowPopupUI(UWorld* WorldContext, TSubclassOf<class UPopUpWidget> WidgetClass);
    void RemovePopupWidget(UWorld* WorldContext, class UPopUpWidget* WidgetToRemove);
    class UPopUpWidget* GetTopmostPopupWidget() const;
    void CloseTopmostPopupWidget(UWorld* WorldContext);

private:
    UPJEUIManager() {}
    static UPJEUIManager* Instance;

    UPROPERTY()
    TArray<TObjectPtr<class UPopUpWidget>> PopupWidgets;

    UPROPERTY()
    TObjectPtr<class UPopUpWidget> TopmostPopupWidget;

    void ShowTopmostPopupWidget(UWorld* WorldContext, class UPopUpWidget* NewTopmostWidget);
    void AddPopupWidget(class UPopUpWidget* NewWidget);

};
