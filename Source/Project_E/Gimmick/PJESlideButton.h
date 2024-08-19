// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "PJESlideButton.generated.h"

class APJECharacterPlayer;
class UPJEMovingComponent;
class APJEPlatform;

UCLASS()
class PROJECT_E_API APJESlideButton : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	APJESlideButton();

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;

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
