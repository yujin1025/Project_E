// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "PJEPressButton.generated.h"

class APJEPlatform;
class UPJEMovingComponent;

UCLASS()
class PROJECT_E_API APJEPressButton : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	APJEPressButton();

protected:
	virtual void BeginPlay() override;
	
	void ActivateButton();
	void CheckActive();
	void NotifyPlatform(bool bActive);

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonBaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UPJEMovingComponent> MovingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component|Mesh|DP_Settings")
	TArray<TObjectPtr<APJEPlatform>> Platforms;
};