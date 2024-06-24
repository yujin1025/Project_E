
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEInteractiveActor.generated.h"

class APJECharacterPlayer;
class UWidgetComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EInteractType : uint8
{
	Click UMETA(DisplayName = "클릭"),
	Hold UMETA(DisplayName = "홀드"),
	Damage UMETA(DisplayName = "다회 클릭"),
	Control UMETA(DisplayName = "조종"),
};


UCLASS()
class PROJECT_E_API APJEInteractiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APJEInteractiveActor();
	
	virtual void InteractionKeyPressed(APJECharacterPlayer* Character);
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character);
	virtual void BreakInteracting();
	
	void ShowPointWidget();
	void HidePointWidget();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void AbleInteraction();
	virtual void DisableInteraction();

	UFUNCTION()
	void NotifyOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void NotifyOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckIsPlayerNearby();
	
public:	
	virtual void Tick(float DeltaTime) override;

	bool bIsPlayerNearby = false;

	// 모든 상호작용 입력은 InteractAble을 통한다
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	bool bIsInteractAble;
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	bool bCanGetController = false;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Root")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Trigger")
	TObjectPtr<UBoxComponent> WidgetTriggerBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Trigger")
	TObjectPtr<UBoxComponent> InteractionTriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Widget")
	TObjectPtr<UWidgetComponent> NotifyInteractionWidget; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Widget")
	TObjectPtr<UWidgetComponent> PointInteractionWidget;
	
	UPROPERTY(EditAnywhere, Category = "Interaction", Replicated)
	bool bIsInteracting;
	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bIsActive;
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	EInteractType InteractType;
};
