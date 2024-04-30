// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJERotationPlatrofm.generated.h"

class UPJERotateComponent;

UCLASS()
class PROJECT_E_API APJERotationPlatrofm : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJERotationPlatrofm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Component")
	TObjectPtr<UStaticMeshComponent> PlatformMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	TObjectPtr<UPJERotateComponent> RotationComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
