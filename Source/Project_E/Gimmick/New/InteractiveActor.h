// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractiveActor.generated.h"

class UWidgetComponent;
enum class EInteractType : uint8;

UCLASS()
class PROJECT_E_API AInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractiveActor();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	UWidgetComponent* NotifyWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Widget")
	UWidgetComponent* InteractionWidget;

	// Variables
	EInteractType InteractType;
	APawn* ControlPawn;

	bool bIsInteractAble;
	bool bIsInteracting;
	bool bIsActivate;

public:
	// Getter & Setters
	FORCEINLINE EInteractType GetInteractType() const { return InteractType; }
};
