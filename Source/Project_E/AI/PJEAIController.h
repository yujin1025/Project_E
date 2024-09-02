// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PJEAIController.generated.h"

class UBlackboardData;
class UBehaviorTree;
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
    void Server_RunAI_Implementation();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_StopAI();
    void Server_StopAI_Implementation();

    virtual void OnPossess(APawn* InPawn) override;

    UBlackboardData* GetBB();

    UBehaviorTree* GetBT();

protected:
    UPROPERTY(EditAnywhere)
    TObjectPtr<UBlackboardData> BBAsset;

    UPROPERTY(EditAnywhere)
    TObjectPtr<UBehaviorTree> BTAsset;

    virtual void InitBB();

    
};