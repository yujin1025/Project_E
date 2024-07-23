#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatWeapon.generated.h"

UCLASS()
class PROJECT_E_API ACatWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemCode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;
};
