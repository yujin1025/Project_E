#include "HealthComponent.h"
#include "../../Game/PJEGameModeBase.h"
#include "../PJECharacterBase.h"
#include "../../Game/PJEGameState.h"
#include "../../Game/PJEPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Character/PJECharacterMonster.h"
#include "Character/Component/PJEHpBarWidgetComponent.h"
#include "UI/PJEHealthBarWidget.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Server_BeginPlay();
}

void UHealthComponent::ChangeHealth(float Amount)
{
	Server_ChangeHealth(Amount);
}

void UHealthComponent::Server_ChangeHealth_Implementation(float Amount)
{
	if (CurrentHealth <= 0)
		return;

	CurrentHealth += Amount;

	OnRep_CurrentHealth();
}

void UHealthComponent::DestroyIfDead()
{
	auto* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character)
	{
		if (CurrentHealth <= 0)
		{
			Character->Destroy(); // 몬스터 애니메이션 나오면 변경하기
		}
		else
		{
			// Character->OnHit();
		}
	}
}

void UHealthComponent::OnRep_HpBarWidgetComponent()
{
	UpdateHpBar();
}

void UHealthComponent::UpdateHpBar()
{
	if (HpBarWidgetComponent)
	{
		HealthBarWidget = Cast<UPJEHealthBarWidget>(HpBarWidgetComponent->GetUserWidgetObject());
		if (HealthBarWidget)
		{
			HealthBarWidget->UpdateHealthBar();
		}
	}
}

void UHealthComponent::OnRep_CurrentHealth()
{
	auto* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character)
	{
		auto* PlayerState = Character->GetPlayerState<APJEPlayerState>();
		if (PlayerState)
		{
			PlayerState->OnChangePlayerHealth(Character->CharacterId, CurrentHealth);
			return;
		}

		auto* GameState = Cast<APJEGameState>(GetWorld()->GetGameState());
		if (!Character->IsPlayer() && GameState)
		{
			GameState->OnChangedHealth(Character->CharacterId, CurrentHealth);
		}
	}

	UpdateHpBar();
	DestroyIfDead();
}

void UHealthComponent::Server_BeginPlay_Implementation()
{
	APJECharacterBase* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character == nullptr)
		return;

	ECharacterType CharacterType = Character->GetCharacterType();

	auto* GameMode = Cast<APJEGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	auto* Data = GameMode->GetCharacterStat(CharacterType);
	if (Data == nullptr)
		return;

	MaxHealth = Data->MaxHp;
	CurrentHealth = MaxHealth;
	HpBarWidgetComponent = Character->FindComponentByClass<UPJEHpBarWidgetComponent>();
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
	DOREPLIFETIME(UHealthComponent, HpBarWidgetComponent);
}

void UHealthComponent::OnRep_MaxHealth()
{
}
