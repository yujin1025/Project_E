// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEAnimNotifyState.h"
#include "../Character/PJECharacterBase.h"

void UPJEAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UPJEAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
}

void UPJEAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}

APJECharacterBase* UPJEAnimNotifyState::GetCharacter(const FOverlapResult& OverlapResult)
{
	auto* Actor = OverlapResult.GetActor();
	if (Actor == nullptr)
		return nullptr;

	return Cast<APJECharacterBase>(Actor);
}

APJECharacterBase* UPJEAnimNotifyState::GetCharacter(USkeletalMeshComponent* MeshComp)
{
	return Cast<APJECharacterBase>(MeshComp->GetOwner());
}