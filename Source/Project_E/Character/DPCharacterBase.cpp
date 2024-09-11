// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DPCharacterBase.h"

ADPCharacterBase::ADPCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADPCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADPCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}