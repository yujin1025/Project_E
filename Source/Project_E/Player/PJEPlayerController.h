// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/PopUpWidget.h"
#include "PJEPlayerController.generated.h"

class UBaseWidget;
class APJEPlayerState;

UENUM(BlueprintType)
enum class EControllerOperation : uint8
{
	ECO_Pawn UMETA(DisplayName = "플레이어 조작"),
	ECO_IgnitionHandle UMETA(DisplayName = "점화손잡이 조작"),
	ECO_Push UMETA(DisplayName = "밀기 조작"),
	ECO_Roll UMETA(DisplayName = "굴리기 조작"),
};

UCLASS()
class PROJECT_E_API APJEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APJEPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	// Switch Input Function
	void InitializeController();
	
	void InitInputPawn();
	void InitInputIgnitionHandle();
	void InitInputPush();
	void InitInputRoll();

	void GameOver();

	UFUNCTION(Client, Reliable)
	void Client_Init();

	FORCEINLINE APawn* GetPlayerPawn() {return PlayerPawn;}

	APJEPlayerState* GetState();
	
protected:
	TObjectPtr<APawn> PlayerPawn = NULL;
	TObjectPtr<AActor> OperatingActor = NULL;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IgnitionHandleContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* CylinderContext;

	UPROPERTY(VisibleAnywhere)
	EControllerOperation ControllerOperation = EControllerOperation::ECO_Pawn;

public:
	FORCEINLINE void SetOperatingActor(AActor* OpActor) { OperatingActor = OpActor; }

//UI
private:
	void OpenWidget();

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UBaseWidget> InGameWindowWidgetClass;

	UPROPERTY()
	UBaseWidget* InGameWindowWidget;

	UPROPERTY()
	TWeakObjectPtr<class UPopUpWidget> SettingsMenu;

	UFUNCTION()
	void ToggleSettingsMenu(const FInputActionValue& Value);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* SettingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputAction* ToggleSettingsMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UPopUpWidget> SettingsMenuClass;
};
