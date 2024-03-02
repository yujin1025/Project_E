// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/PJECharacterStatComponent.h"

// Sets default values for this component's properties
UPJECharacterStatComponent::UPJECharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

float UPJECharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}

	return ActualDamage;
}


void UPJECharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetHp(100);
}

// Called when the game starts
void UPJECharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPJECharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, 1000/*MaxHp*/);

	OnHpChanged.Broadcast(CurrentHp);
}


// Called every frame
void UPJECharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

