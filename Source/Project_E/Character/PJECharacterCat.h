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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UDataTable* ItemDatabase;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwingAction;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float DashSpeed = 1.5f;


protected:
	void Grab();
	void Swing();
	void Dash();

private:
	UPROPERTY()
	UCatInventoryWidget* CatInventoryWidget;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UCatInventoryWidget> CatInventoryClass;
};