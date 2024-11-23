// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Projectile/CatWeapon.h"
#include "PJECharacterBase.generated.h"


class UHealthComponent;
class UHitDeadComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class PROJECT_E_API APJECharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APJECharacterBase();

protected:
	virtual void BeginPlay() override;

	virtual void SetDead();

	float DeadEventDelayTime = 5.0f;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	bool IsTarget = false;

	void Move(const FVector2D Value);
	virtual void Look(const FVector2D Value);
	virtual void OnHit();
	virtual void OnDie();


public:
	bool IsPlayer(); //플레이어인지 여부

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Id, meta = (AllowPrivateAccess = "true"))
	int CharacterId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	UHitDeadComponent* HitDeadComponent;

	UFUNCTION(BlueprintCallable, Category = "Character")
	ECharacterType GetCharacterType() const { return CharacterType; }

	virtual ACatWeapon* GetEquippedWeapon() const { return nullptr; }

protected:
	// Character type
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	ECharacterType CharacterType;

public:
	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget);

	bool bIsAttacking = false;

	// 공격 애니메이션 끝났을 때 호출되는 델리게이트
	FOnAttackEndDelegate OnAttackEnd;

	// 델리게이트 핸들러 함수
	UFUNCTION()
	void OnAttackEndHandler();

// Hp Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Motion, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComponent;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};