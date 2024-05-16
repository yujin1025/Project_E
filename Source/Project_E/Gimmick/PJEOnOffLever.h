#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEOnOffLever.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class PROJECT_E_API APJEOnOffLever : public AActor
{
	GENERATED_BODY()
	
public:	
	APJEOnOffLever();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> LeverBaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> LeverMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<UBoxComponent> InteractableBoxCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<UWidgetComponent> ShowInteractableWidget;

	
	

};
