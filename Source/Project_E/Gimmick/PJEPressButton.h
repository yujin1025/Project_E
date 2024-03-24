// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJEPressButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEPressButton : public APJEButtonBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	virtual void Tick(float DeltaSeconds) override;
};
