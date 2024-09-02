// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterMonster.h"
#include "NavigationSystem.h"
#include "Project_E/Character/Component/PJEHpBarWidgetComponent.h"
#include "UI/PJEHealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Component/HealthComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
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
	if (OtherActor->IsA(APJECharacterPlayer::StaticClass()))
	{
		FVector PlayerVelocity = OtherActor->GetVelocity();

		if (PlayerVelocity.Size() > MinimumPlayerSpeed)
		{
			// 플레이어와 몬스터 간의 벡터 계산
			FVector PlayerLocation = OtherActor->GetActorLocation();
			FVector MonsterLocation = GetActorLocation();
			FVector PlayerToMonsterVector = (MonsterLocation - PlayerLocation).GetSafeNormal();

			// 플레이어의 정면 벡터 계산
			FVector PlayerForwardVector = OtherActor->GetActorForwardVector().GetSafeNormal();

			// 두 벡터 간의 각도 계산
			float DotProduct = FVector::DotProduct(PlayerToMonsterVector, PlayerForwardVector);
			float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

			// 각도가 0에서 90도 사이인지 확인
			if (Angle >= 0.0f && Angle <= 90.0f)
			{
				FVector PushDirection = (GetActorLocation() - OtherActor->GetActorLocation()).GetSafeNormal();
				FVector Impulse = PushDirection * PushStrength;
				GetCharacterMovement()->AddImpulse(Impulse, true);
			}
		}
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
