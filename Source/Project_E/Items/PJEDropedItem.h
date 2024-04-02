// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemBase.h"
#include "PJEDropedItem.generated.h"

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
	virtual void BeginInteracting(const AActor* InteractActor) override;
	virtual void EndInteracting(const AActor* InteractActor) override;

	//void GetItem(const AActor* InteractActor);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ItemCode;
};
