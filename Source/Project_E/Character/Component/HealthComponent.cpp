#include "HealthComponent.h"
#include "../../Game/PJEGameModeBase.h"
#include "../PJECharacterBase.h"
#include "../../Game/PJEGameState.h"
#include "../../Game/PJEPlayerState.h"
#include "Net/UnrealNetwork.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentHealth = MaxHealth;
	SetIsReplicatedByDefault(true); // 컴포넌트를 복제하도록 설정
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

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
}

void UHealthComponent::ChangeHealth(float Amount)
{
	if (CurrentHealth <= 0)
		return;

	CurrentHealth += Amount;

	auto* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character == nullptr)
		return;

	auto* PlayerState = Character->GetPlayerState<APJEPlayerState>();
	if (Character->IsPlayer() && PlayerState)
	{
		PlayerState->OnChangePlayerHealth(Character->CharacterId, CurrentHealth);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Player Number : (%d) Current Health: %f"), Character->CharacterId, CurrentHealth));

	}

	auto* GameState = Cast<APJEGameState>(GetWorld()->GetGameState());
	if (!Character->IsPlayer() && GameState)
	{
		GameState->OnChangedHealth(Character->CharacterId, CurrentHealth);
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Non Player Number : (%d) Current Health: %f"), Character->CharacterId, CurrentHealth));

	}

	Server_ChangeHealth(CurrentHealth);

	if (Amount < 0)
	{
		if (CurrentHealth <= 0)
		{
			Character->Destroy(); //몬스터 애니메이션 나오면 변경하기
			//Character->OnDie();
		}
		else
		{
			//Character->OnHit();
		}
	}
}

void UHealthComponent::Server_ChangeHealth_Implementation(float Health)
{
	CurrentHealth = Health;
	OnRep_Health();
}

void UHealthComponent::OnRep_Health()
{
	auto* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character)
	{
		auto* PlayerState = Character->GetPlayerState<APJEPlayerState>();
		if (PlayerState)
		{
			PlayerState->OnChangePlayerHealth(Character->CharacterId, CurrentHealth);
		}
	}
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}
