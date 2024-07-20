
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Item")
	int32 ItemCode;

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;
	
public:	
	FORCEINLINE void SetItemCode(int32 NewItemCode) { ItemCode = NewItemCode; }
};
