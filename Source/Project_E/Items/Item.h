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
    int32 ItemCode;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    FString Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    EItemType Type;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    float Weight;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    float CatDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    float DuckDamage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    UTexture2D* ItemImage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ACatWeapon> CatWeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ADuckProjectile> DuckWeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ADropItem> DropItmeClass;

    FString GetItemName() const { return Name; }

    static UItem* SetItem(const UDataTable* ItemDataTable, int32 Code);
};

USTRUCT()
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    int32 ItemCode; 

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    EItemType Type;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float Weight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float CatDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    float DuckDamage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    UTexture2D* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ACatWeapon> CatWeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ADuckProjectile> DuckWeaponClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<class ADropItem> DropItmeClass;
};