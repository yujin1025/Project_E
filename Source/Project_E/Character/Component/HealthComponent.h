#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE(FOnHealthChangeDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	float MaxHealth;

	UFUNCTION()
	void OnRep_MaxHealth();

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	UFUNCTION()
	void OnRep_CurrentHealth();

public:
	FOnHealthChangeDelegate OnHealthChanged;

	void ChangeHealth(float Amount);

	UFUNCTION(Server, Reliable)
	void Server_ChangeHealth(float Amount);
	void Server_ChangeHealth_Implementation(float Amount);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	float GetMaxHealth() const { return MaxHealth; }

	void DestroyIfDead();

// HP Bar Section
protected:
	UPROPERTY()
	TObjectPtr<class UPJEHealthBarWidget> HealthBarWidget;

	UPROPERTY()
	TObjectPtr<class UPJEHpBarWidgetComponent> HpBarWidgetComponent;
};
