// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Item.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon,
	NonWeapon
};

UCLASS(Blueprintable, BlueprintType)
class PROJECT_E_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
    UItem();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FString Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    EItemType Type;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    float Weight;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    float Damage;

    FString GetItemName() const { return Name; }
};

USTRUCT()
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float Damage;
};