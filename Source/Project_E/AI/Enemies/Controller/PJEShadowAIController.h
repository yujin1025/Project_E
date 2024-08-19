// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/PJEAIController.h"
#include "PJEShadowAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEShadowAIController : public APJEAIController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(ReplicatedUsing = OnRep_NextPatrolPos)
	FVector NextPatrolPos;

    UPROPERTY(ReplicatedUsing = OnRep_SubPatrolPos)
    FVector SubPatrolPos;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    virtual void OnRep_NextPatrolPos();

    UFUNCTION()
    virtual void OnRep_SubPatrolPos();

public:
    APJEShadowAIController();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_SetRandomDestPos(const FVector& DestPos);

    virtual void Server_SetRandomDestPos_Implementation(const FVector& DestPos);
    virtual bool Server_SetRandomDestPos_Validate(const FVector& DestPos);
};
