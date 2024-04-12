// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadow.h"

APJECharacterShadow::APJECharacterShadow()
{
	ShadowSpawnRadius = 1000.0f;
}

void APJECharacterShadow::SetShadowGeneratorsCount(int32 NewShadowGeneratorsCount)
{
	ShadowGeneratorsCount = NewShadowGeneratorsCount;
}

float APJECharacterShadow::GetShadowSpawnRadius()
{
	return ShadowSpawnRadius;
}
