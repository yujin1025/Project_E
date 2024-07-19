// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackEnd.h"
#include "../Character/PJECharacterBase.h"

void UAnimNotifyAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	APJECharacterBase* character = Cast<APJECharacterBase>(owner);
	if (character != nullptr)
	{
		character->OnAttackEnd.Broadcast();
	}
}
