// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterMonster.h"
#include "NavigationSystem.h"
#include "Project_E/Character/Component/PJEHpBarWidgetComponent.h"
#include "UI/PJEHealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Component/HealthComponent.h"

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

		// 상대 위치 설정
		HealthBarComponent->SetRelativeLocation(FVector(0.0f, 0.0f, CapsuleHalfHeight + HealthBarOffset));
	}
}

void APJECharacterMonster::BeginPlay()
{
	Super::BeginPlay();
}

void APJECharacterMonster::OnDeath()
{
	GetWorld()->GetTimerManager().SetTimer(DestructionTimer, this, &APJECharacterMonster::DelayedDestroy, 1.0f, false);
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

/*
float APJECharacterMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ReturnFloat = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// UpdateHealthBar();

	return ReturnFloat;
}


void APJECharacterMonster::UpdateHealthBar()
{
	if (UPJEHealthBarWidget* HealthBar = Cast<UPJEHealthBarWidget>(HealthBarComponent->GetUserWidgetObject()))
	{
		if (HealthComponent)
		{
			HealthBar->UpdateHealthBar(HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());
		}
	}
}
*/