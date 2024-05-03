// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJERotateComponent.h"
#include "GameFramework/Actor.h"
#include "PJERotatingPlatform.generated.h"

class UPJERotateComponent;

UCLASS()
class PROJECT_E_API APJERotatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	APJERotatingPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PlatformMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UPJERotateComponent> RotationComponent;

public:
	
};
