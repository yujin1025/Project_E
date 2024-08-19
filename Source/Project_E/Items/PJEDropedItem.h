// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PJEDropedItem.generated.h"

class UWidgetComponent;
/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEDropedItem : public AItemBase
{
	GENERATED_BODY()

public:
	APJEDropedItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetItemCode(int32 NewItemCode);

protected:
	virtual void BeginPlay() override;

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;
	virtual void InteractionKeyReleased(APJECharacterPlayer* Character) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ItemCode;
};