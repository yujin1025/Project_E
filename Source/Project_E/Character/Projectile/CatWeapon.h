#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEInteractiveActor.h"
#include "CatWeapon.generated.h"

UCLASS()
class PROJECT_E_API ACatWeapon : public APJEInteractiveActor
{
	GENERATED_BODY()

public:
	ACatWeapon();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float DamageAmount = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CollisionComponent;

	void SetDamage(float Damage);

	float GetDamageAmount() const { return DamageAmount; }

	UFUNCTION()
	void OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "item")
	int32 ItemCode;

protected:
	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Weapon();
};
