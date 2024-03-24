// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractInterface.h"
#include "GameFramework/Actor.h"
#include "PJEDropItem.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_E_API APJEDropItem : public AActor, public IPJEInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEDropItem();

protected:
	virtual void BeginInteracting() override;
	virtual void EndInteracting() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ItemMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> WidgetTrigger;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
