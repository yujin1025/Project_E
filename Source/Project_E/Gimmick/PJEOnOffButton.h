// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "Gimmick/PJEButtonBase.h"
#include "PJEOnOffButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEOnOffButton : public APJEButtonBase, public IPJEInteractInterface
{
	GENERATED_BODY()

public:
	APJEOnOffButton();

	/** Button Interface */
	virtual void ShowInteractWidget() override;
	virtual void HideInteractWidget() override;
	/** end Button Interface */

protected:
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	virtual void Tick(float DeltaTime) override;
	
};
