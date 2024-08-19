
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "DropItem.generated.h"

UCLASS()
class PROJECT_E_API ADropItem : public APJEInteractiveActor
{
	GENERATED_BODY()
	
public:	
	ADropItem();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> ItemMesh;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "DP_Settings")
	int32 ItemCode;

	
public:	
	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

	FORCEINLINE void SetItemCode(int32 NewItemCode) { ItemCode = NewItemCode; }
};
