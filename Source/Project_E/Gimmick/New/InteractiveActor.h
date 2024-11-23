// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "InteractiveActor.generated.h"

class UBoxComponent;
class UWidgetComponent;
enum class EInteractType : uint8;

UCLASS()
class PROJECT_E_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractiveActor();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Interaction Function
	virtual void InteractionKeyPressed();
	virtual void InteractionKeyReleased();
	virtual void BreakInteracting();

	// Widget Function
	void DisplayNotifyWidget(bool bDisplay);
	void DisplayInteractionWidget(bool bDisplay);

protected:
	virtual void BeginPlay() override;
	virtual void SetInteraction(bool bCanInteract);
	
private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Root")
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	UBoxComponent* InteractionBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	UWidgetComponent* NotifyWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	UWidgetComponent* InteractionWidget;

	// Variables
	EInteractType InteractType;

	UPROPERTY(Replicated)
	APawn* ControlPawn;
	UPROPERTY(Replicated)
	bool bIsInteractAble;
	UPROPERTY(Replicated)
	bool bIsInteracting;
	UPROPERTY(Replicated)
	bool bIsActivate;

public:
	// Getter & Setters
	FORCEINLINE EInteractType GetInteractType() const { return InteractType; }
	FORCEINLINE APawn* GetControlPawn() const { return ControlPawn; }
	FORCEINLINE bool GetIsInteracting() const { return bIsInteracting; }
	FORCEINLINE bool GetIsInteractAble() const { return bIsInteractAble; }
	FORCEINLINE bool GetIsActivate() const { return bIsActivate; }

	FORCEINLINE void SetInteractType(const EInteractType NewInteractType) { InteractType = NewInteractType; }
	FORCEINLINE void SetControlPawn(APawn* NewControlPawn) { ControlPawn = NewControlPawn; }
	FORCEINLINE void SetIsInteracting(const bool NewIsInteracting) { bIsInteracting = NewIsInteracting; }
	FORCEINLINE void SetIsInteractAble(const bool NewIsInteractAble) { bIsInteractAble = NewIsInteractAble; }
	FORCEINLINE void SetIsActivate(const bool NewIsActivate) { bIsActivate = NewIsActivate; }
};
