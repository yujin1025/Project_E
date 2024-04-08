// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEIgnitionHandle.generated.h"

class APJECharacterPlayer;
class UPJERotationPlatform;

UCLASS()
class PROJECT_E_API APJEIgnitionHandle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEIgnitionHandle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BindInput();
	
	void OperateClockwiseTurn();
	void OperateCounterClockwiseTurn();
	void IntteruptRotation();

	void SetCharacter(APJECharacterPlayer* PlayerCharacter);
	
	
protected:
	UPROPERTY(EditAnywhere, Category="Platform")
	TArray<TObjectPtr<AActor>> RotationPlatforms;

	TObjectPtr<APJECharacterPlayer> Character = nullptr;
};
