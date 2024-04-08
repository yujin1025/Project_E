// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "SlotWidget.generated.h"

class UImage;
//class UItem;
/**
 * 
 */
UCLASS()
class PROJECT_E_API USlotWidget : public UBaseWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UImage* ItemImg; // Image widget to display item image

    // Function to set item image
    UFUNCTION(BlueprintCallable)
    void SetItemImage(UTexture2D* ItemImage);

    // Function to check if slot is occupied
    UFUNCTION(BlueprintPure)
    bool IsOccupied() const;

private:
    UTexture2D* CurrentItemImage;
};
