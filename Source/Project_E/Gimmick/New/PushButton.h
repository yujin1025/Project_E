
#pragma once

#include "CoreMinimal.h"
#include "Gimmick/New/InteractiveActor.h"
#include "PushButton.generated.h"

UCLASS()
class PROJECT_E_API APushButton : public AInteractiveActor
{
	GENERATED_BODY()

public:
	APushButton();
	virtual void Tick(float DeltaSeconds) override;

	// Interaction Function
	virtual void InteractionKeyPressed() override;
	virtual void InteractionKeyReleased() override;
	
protected:
	virtual void BeginPlay() override;
	
	void MoveButton(float DeltaSeconds);
	virtual void BreakInteracting() override;
	
	
private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Mesh")
	UStaticMeshComponent* ButtonBase;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Mesh")
	UStaticMeshComponent* ButtonMesh;

	// Variables
	FVector	OriginButtonLocation;
	UPROPERTY(EditAnywhere, Category = "DP_Settings")
	FVector ButtonMovementOffset;
	UPROPERTY(EditAnywhere, Category = "DP_Settings")
	float ButtonMoveSpeed = 10.f;
};
