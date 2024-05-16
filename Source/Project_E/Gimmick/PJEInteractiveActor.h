
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEInteractiveActor.generated.h"

class UWidgetComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	Click UMETA(DisplayName = "클릭"),
	Hold UMETA(DisplayName = "홀드"),
	Damage UMETA(DisplayName = "다회 클릭")
};



UCLASS()
class PROJECT_E_API APJEInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APJEInteractiveActor();

protected:
	virtual void BeginPlay() override;

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void ShowPointInteractionWidget();
	void HidePointInteractionWidget();

	void InteractionKeyPressed();
	void InteractionKeyReleased();
	
	
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Trigger")
	TObjectPtr<UBoxComponent> WidgetTriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Trigger")
	TObjectPtr<UBoxComponent> InteractionTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Widget")
	TObjectPtr<UWidgetComponent> InteractionWidget; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Widget")
	TObjectPtr<UWidgetComponent> PointInteractionWidget;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	bool bIsInteracting;
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	bool bIsActive;
	
};
