// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJESlideButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJESlideButton : public APJEButtonBase
{
	GENERATED_BODY()

protected:
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
