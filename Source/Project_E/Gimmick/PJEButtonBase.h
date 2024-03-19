// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PJEButtonBase.generated.h"

class APJEPlatform;
class UBoxComponent;

UCLASS()
class PROJECT_E_API APJEButtonBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APJEButtonBase();

protected:
	virtual void BeginPlay() override;

	void MoveButton(float DeltaTime);

	UFUNCTION()
	virtual void ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	virtual void ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void NotifyActiveToPlatform(bool ButtonActive);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool bButtonActive = false;
	
protected:
	// Button Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> ButtonTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonBorderMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ButtonMesh;

	UPROPERTY(VisibleAnywhere)
	bool bButtonInteract = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector OriginLocation;
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector MoveOffset;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveTime;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<APJEPlatform>> Platforms;
	
	// To be removed later
	APawn* Character;

};
