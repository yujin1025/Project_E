// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJECharacterPlayer.h"
#include "PJECharacterCat.generated.h"

/**
 *
 */
UCLASS()
class PROJECT_E_API APJECharacterCat : public APJECharacterPlayer
{
	GENERATED_BODY()

public:
	APJECharacterCat();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwingAction;

protected:
	void Grab() override; 
	void Swing();
};