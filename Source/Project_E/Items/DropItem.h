
#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "DropItem.generated.h"

UCLASS()
class PROJECT_E_API ADropItem : public APJEInteractiveActor
{
	GENERATED_BODY()
	
public:	
	ADropItem();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "DP_Settings")
	int32 ItemCode;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

	FORCEINLINE void SetItemCode(int32 NewItemCode) { ItemCode = NewItemCode; }
};
