// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDeadComponent.h"
#include "../PJECharacterBase.h"


void UHitDeadComponent::PlayHitMontage()
{
	APJECharacterBase* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character == nullptr)
		return;

	Character->PlayAnimMontage(HitMontage);
}

void UHitDeadComponent::PlayDeadMontage()
{
	APJECharacterBase* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character == nullptr)
		return;

	Character->PlayAnimMontage(DeadMontage);
}