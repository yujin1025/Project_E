// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterShadowA.h"
#include "AI/Enemies/Controller/PJEShadowAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"
#include "AI/Enemies/PJEShadowArea.h"

APJECharacterShadowA::APJECharacterShadowA()
{
	ShadowGeneratorsCount = 0;

	MonsterRank = EMonsterRank::Normal;
	MaxHp = 50;
	MoveSpeed = 2.0f;
	PlayerDetectionRange = 4.0f;
	MaxKeepMovingTime = 4.0f;
	BlinkDuration = 0.6f;
	TeleportRange = 2.0f;
	SingleBlinkDuration = 0.2f;

	LaughAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("LaughAudioComponent"));
	LaughAudioComponent->SetupAttachment(RootComponent);
}

void APJECharacterShadowA::Destroyed()
{
	if (ShadowArea)
	{
		ShadowArea->ShadowAArr.Remove(this);
		ShadowArea->PlayShadowASound();
	}
	Super::Destroyed();
}

float APJECharacterShadowA::GetMaxKeepMovingTime()
{
	return MaxKeepMovingTime;
}

float APJECharacterShadowA::GetBlinkDuration()
{
	return BlinkDuration;
}

float APJECharacterShadowA::GetSingleBlinkDuration()
{
	return SingleBlinkDuration;
}

float APJECharacterShadowA::GetTeleportRange()
{
	return TeleportRange * 100.0f;
}

float APJECharacterShadowA::GetRunAwaySpeed()
{
	return RunAwaySpeed * 100;
}

float APJECharacterShadowA::GetPlayerDetectRange()
{
	return PlayerDetectionRange * 100.0f;
}

float APJECharacterShadowA::GetDetectMaxYDifference()
{
	return MaxYDifference;
}

float APJECharacterShadowA::GetDetectMinYDifference()
{
	return MinYDifference;
}

void APJECharacterShadowA::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	SetCurrentHP(MaxHp);
}

void APJECharacterShadowA::PlaySound()
{
	if (LaughSound)
	{
		if (LaughAudioComponent && !LaughAudioComponent->IsPlaying())
		{
			LaughAudioComponent->SetSound(LaughSound);
			LaughAudioComponent->AttenuationSettings = LaughAttenuation;
			LaughAudioComponent->Play();
		}
	}
}

void APJECharacterShadowA::StopSound()
{
	if (LaughAudioComponent && LaughAudioComponent->IsPlaying())
	{
		LaughAudioComponent->Stop();
	}
}

void APJECharacterShadowA::SetLaughVolume(float Volume)
{
	if (LaughAudioComponent)
	{
		LaughAudioComponent->SetVolumeMultiplier(FMath::Clamp(Volume, 0.0f, 1.0f));
	}
}
