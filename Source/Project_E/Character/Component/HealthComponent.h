#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


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
	float MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float CurrentHealth;

	UFUNCTION()
	void OnRep_Health();

public:
	void ChangeHealth(float Amount);

	UFUNCTION(Server, Reliable)
	void Server_ChangeHealth(float Amount);
		
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	float GetMaxHealth() const { return MaxHealth; }

};
