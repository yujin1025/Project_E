// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PJEAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API APJEAIController : public AAIController
{
    GENERATED_BODY()

    public:
    APJEAIController();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void RunAI();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void StopAI();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_RunAI();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_StopAI();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_RunAI();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_StopAI();

    virtual void OnPossess(APawn* InPawn) override;

    UFUNCTION()
    void OnRep_BBAsset();

    UFUNCTION()
    void OnRep_BTAsset();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    TObjectPtr<class UBlackboardData> GetBB();

    TObjectPtr<class UBehaviorTree> GetBT();

protected:
    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_BBAsset)
    TObjectPtr<class UBlackboardData> BBAsset;

    UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_BTAsset)
    TObjectPtr<class UBehaviorTree> BTAsset;

    virtual void InitBB();

    
};