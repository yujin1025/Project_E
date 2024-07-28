// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PJEInteractiveActor.h"
#include "GameFramework/Actor.h"
#include "BallFlower.generated.h"

UCLASS()
class PROJECT_E_API ABallFlower : public APJEInteractiveActor
{
	GENERATED_BODY()
	
public:	
	ABallFlower();

protected:
	virtual void BeginPlay() override;

	virtual void InteractionKeyPressed(APJECharacterPlayer* Character) override;

	UFUNCTION(Server, Reliable)
	void Server_GetBall();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_GetBall();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Mesh")
	UStaticMeshComponent* FlowerMesh;

	UPROPERTY(EditAnywhere)
	UMaterial* TransparentMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "DP_Settings")
	int32 ItemCode;
};