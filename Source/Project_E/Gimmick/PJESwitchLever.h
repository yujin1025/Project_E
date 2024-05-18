#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "PJESwitchLever.generated.h"

class UPJERotateComponent;

UCLASS()
class PROJECT_E_API APJESwitchLever : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	APJESwitchLever();

protected:
	virtual void InteractionKeyReleased() override;

	void ActivateLever();
	
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> LeverBaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh");
	TObjectPtr<USceneComponent> LeverPivot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Mesh")
	TObjectPtr<UStaticMeshComponent> LeverMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component|Function")
	TObjectPtr<UPJERotateComponent> RotateComponent;

	//TEST FUNCTION
private:
	void TEST_FUNCTION();	
};
