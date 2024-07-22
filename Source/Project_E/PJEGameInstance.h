#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PJEGameInstance.generated.h"

UCLASS()
class PROJECT_E_API UPJEGameInstance : public UGameInstance
{
	GENERATED_BODY()

	public:
	virtual void OnStart() override;
	virtual void Shutdown() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> SettingsMenuClass;

private:
	UUserWidget* SettingsMenu;
};
