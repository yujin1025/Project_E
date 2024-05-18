// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PJECharacterBase.generated.h"

class UHealthComponent;

UCLASS()
class PROJECT_E_API APJECharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APJECharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

// Dead Section
protected:
	virtual void SetDead();

	float DeadEventDelayTime = 5.0f;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	bool IsTarget = false;

	void Move(const FVector2D Value);
	virtual void Look(const FVector2D Value);

public:
	bool IsPlayer(); //플레이어인지 여부

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Id, meta = (AllowPrivateAccess = "true"))
	int CharacterId;

	UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable, Category = "Character")
	ECharacterType GetCharacterType() const { return CharacterType; }

protected:
	// Character type
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	ECharacterType CharacterType;

public:
	virtual FVector GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget);
};