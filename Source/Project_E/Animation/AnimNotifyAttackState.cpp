// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyAttackState.h"
#include "../Character/PJECharacterBase.h"
#include "../Character/Component/HealthComponent.h"
#include "../Character/Projectile/CatWeapon.h"

//공격 범위 내에 있는 대상을 찾아 데미지를 가함
void UAnimNotifyAttackState::TryAttack(USkeletalMeshComponent* MeshComp)
{
	if (CurrentAttackCount >= 1)
		return;

	APJECharacterBase* MyCharacter = Cast<APJECharacterBase>(MeshComp->GetOwner());
	if (MyCharacter == nullptr)
		return;

	float WeaponDamageAmount = DamageAmount;
	AActor* EquippedWeaponActor = MyCharacter->GetEquippedWeapon();
	if (ACatWeapon* EquippedWeapon = Cast<ACatWeapon>(EquippedWeaponActor))
	{
		WeaponDamageAmount = EquippedWeapon->GetDamageAmount();
	}

	TArray<APJECharacterBase*> TargetCharacters;
	if (TryGetOverlapTargets(MyCharacter, TargetCharacters))
	{
		for (auto* TargetCharacter : TargetCharacters)
		{
			UHealthComponent* DamagedHealthComponent = TargetCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent)
			{
				DamagedHealthComponent->ChangeHealth(-WeaponDamageAmount);
				CurrentAttackCount++;
			}
		}
	}
}

void UAnimNotifyAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	TryAttack(MeshComp);
}

void UAnimNotifyAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	CurrentAttackCount = 0;
}

//주어진 캐릭터의 위치를 중심으로 범위 내에 있는 캐릭터를 검색
bool UAnimNotifyAttackState::TryGetOverlapResult(APJECharacterBase* Owner, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Owner ? Owner->GetWorld() : nullptr;
	if (World == nullptr)
		return false;

	FVector Center = Owner->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Owner);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center + CenterOffset,
		Owner->GetActorQuat(),
		ECollisionChannel::ECC_Pawn, //나중에 충돌설정 변경하기
		FCollisionShape::MakeSphere(100.0f),
		CollisionParam);

	return bResult;
}

//주어진 캐릭터를 중심으로 공격 범위 내에 있는 대상을 검색
bool UAnimNotifyAttackState::TryGetOverlapTargets(APJECharacterBase* Character, OUT TArray<APJECharacterBase*>& FoundTargets)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			bResult = true;
			FoundTargets.Add(TargetCharacter);
			break;
		}
	}

	return bResult;
}
