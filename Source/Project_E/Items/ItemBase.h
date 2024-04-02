// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gimmick/PJEInteractInterface.h"
#include "ItemBase.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_E_API AItemBase : public AActor, public IPJEInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	//UItem* Item;

	//UFUNCTION(BlueprintCallable, Category = "Item")
	//void SetItem(const FString& ItemName);

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<UBoxComponent> WidgetTrigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
