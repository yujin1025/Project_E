// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/PJEAnimNotifyState.h"
#include "AnimNotifyAttackState.generated.h"

class APJECharacterBase;
/**
 * 
 */
UCLASS()
class PROJECT_E_API UAnimNotifyAttackState : public UPJEAnimNotifyState
{
	GENERATED_BODY()
	
public:
	void TryAttack(USkeletalMeshComponent* MeshComp);
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	bool TryGetOverlapResult(APJECharacterBase* Owner, TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTargets(APJECharacterBase* Character, OUT TArray<APJECharacterBase*>& FoundTargets);

protected:
	int CurrentAttackCount = 0;

	UPROPERTY(EditAnywhere)
	FVector CenterOffset;

	UPROPERTY(EditAnywhere)
	int DamageAmount;
};
