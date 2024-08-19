// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "CatAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_E_API UCatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UFUNCTION()
	void AnimNotify_R_DashTrail();

	UFUNCTION()
	void AnimNotify_L_DashTrail();

	UFUNCTION()
	void AnimNotify_Land();

private:
	UPROPERTY(BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = true))
	class APJECharacterPlayer* CatCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Particle")
	UNiagaraSystem* DashEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true), Category = "Particle")
	UNiagaraSystem* LandEffect;
};
