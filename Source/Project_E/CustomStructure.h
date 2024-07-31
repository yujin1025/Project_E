// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CustomStructure.generated.h"

USTRUCT(BlueprintType)
struct FDoorKeyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UStaticMesh* DoorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UStaticMesh* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DoorNum;
};

UCLASS()
class PROJECT_E_API ACustomStructure : public AActor
{
	GENERATED_BODY()
};
