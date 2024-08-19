#pragma once

#include "CoreMinimal.h"
#include "PJERotateComponent.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "PJESwitchLever.generated.h"

class APJECharacterPlayer;
class APJEPlatform;
class UPJERotateComponent;

UCLASS()
class PROJECT_E_API APJESwitchLever : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	APJESwitchLever();

protected:
	virtual void BeginPlay() override;
	
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;

	void ActivateLever();

	void CheckActive();
	void NotifyPlatform(bool bActive);
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> LeverBaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh");
	TObjectPtr<USceneComponent> LeverPivot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> LeverMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Function")
	TObjectPtr<UPJERotateComponent> RotateComponent;

	UPROPERTY(EditAnywhere, Category = "Interaction|Platform|DP_Settings")
	TArray<TObjectPtr<APJEPlatform>> Platforms;
};
