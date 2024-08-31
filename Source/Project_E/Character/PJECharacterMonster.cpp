// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterMonster.h"
#include "NavigationSystem.h"
#include "Project_E/Character/Component/PJEHpBarWidgetComponent.h"
#include "UI/PJEHealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Component/HealthComponent.h"
#include "Character/PJECharacterPlayer.h"

APJECharacterMonster::APJECharacterMonster()
{
	HealthBarComponent = CreateDefaultSubobject<UPJEHpBarWidgetComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(RootComponent);
	if (HealthBarComponent->GetHpBarWidgetClass())
	{
		HealthBarComponent->SetWidgetClass(HealthBarComponent->GetHpBarWidgetClass());
		HealthBarComponent->SetDrawSize(FVector2D(100, 20));
		HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		
	}

	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		float CapsuleHalfHeight = CapsuleComp->GetScaledCapsuleHalfHeight();
		float HealthBarOffset = 50.0f;

		// ��� ��ġ ����
		HealthBarComponent->SetRelativeLocation(FVector(0.0f, 0.0f, CapsuleHalfHeight + HealthBarOffset));
	}

	GetMesh()->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void APJECharacterMonster::BeginPlay()
{
	Super::BeginPlay();
}

void APJECharacterMonster::OnDeath()
{
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &APJECharacterMonster::DelayedDestroy, 1.0f, false);
}

void APJECharacterMonster::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// �÷��̾�� �浹�� ��� ó��
	if (OtherActor->IsA(APJECharacterPlayer::StaticClass()))
	{
		// �浹 ������ �ݴ� �������� �о��
		FVector PushDirection = Hit.ImpactNormal * -1.0f;
		PushDirection.Z = 0.0f; // ���� �������� �� ���ϱ� (Y������ �и��� �ʰ�)

		float PushStrength = 1000.0f; // Impulse�� ���� ����
		GetMesh()->AddImpulse(PushDirection * PushStrength, NAME_None, true); // Impulse ����
	}
}

void APJECharacterMonster::DelayedDestroy()
{
	Destroy();
}

void APJECharacterMonster::SetCurrentHP(int32 NewHp)
{
	CurrentHp = NewHp;
}

int32 APJECharacterMonster::GetCurrentHP() const
{
	return CurrentHp;
}

float APJECharacterMonster::GetMoveSpeed() const
{
	return MoveSpeed;
}
