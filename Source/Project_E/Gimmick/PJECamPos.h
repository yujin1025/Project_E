// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJECamPos.generated.h"

class UArrowComponent;

UCLASS()
class PROJECT_E_API APJECamPos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJECamPos();

	FVector GetArrowLocation() const;
	FRotator GetArrowRotation() const;
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UArrowComponent> ArrowComponent;
};
