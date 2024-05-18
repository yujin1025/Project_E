#include "HealthComponent.h"
#include "../../Game/PJEGameModeBase.h"
#include "../PJECharacterBase.h"
#include "../../Game/PJEGameState.h"
#include "../../Game/PJEPlayerState.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

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

	//auto* Data = GameMode->GetCharacterStat(CharacterType);
	//if (Data == nullptr)
	//	return;

	//MaxHealth = Data->MaxHp;
	//CurrentHealth = MaxHealth;
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::ChangeHealth(float Amount)
{
	auto* GameMode = Cast<APJEGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	if (CurrentHealth <= 0)
		return;

	CurrentHealth += Amount;

	auto* Character = Cast<APJECharacterBase>(GetOwner());
	if (Character == nullptr)
		return;

	if (Character->IsPlayer()) 
	{
		GameMode->MyPlayerState->OnChangePlayerHealth(Character->CharacterId, CurrentHealth);
		UE_LOG(LogTemp, Warning, TEXT("Player Number : (%d) Current Health: %d"), Character->CharacterId, CurrentHealth);
	}
	else 
	{
		GameMode->MyGameState->OnChangedHealth(Character->CharacterId, CurrentHealth);
		UE_LOG(LogTemp, Warning, TEXT("Non Player Number : (%d) Current Health: %d"), Character->CharacterId, CurrentHealth);
	}

	if (Amount < 0)
	{
		if (CurrentHealth <= 0)
		{
			//Character->OnDie();
		}
		else
		{
			//Character->OnHit();
		}
	}
}

