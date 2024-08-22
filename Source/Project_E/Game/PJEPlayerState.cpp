// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEPlayerState.h"

#include "Net/UnrealNetwork.h"

APJEPlayerState::APJEPlayerState()
{
	PlayerRole = EPlayerRole::Cat;
}

void APJEPlayerState::OnChangePlayerHealth(int objectId, float Amount)
{
	if (OnPlayerHPChanged.IsBound())
	{
		OnPlayerHPChanged.Broadcast(objectId, Amount);
	}
}

void APJEPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, PlayerRole);
}

void APJEPlayerState::CopyProperties(APlayerState* NewPlayerState)
{
	Super::CopyProperties(NewPlayerState);

	FString PlayerRoleString = (this->GetPlayerRole() == EPlayerRole::Cat) ? TEXT("Cat") : TEXT("Duck");

	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Replicaate PlayerRole : %s"), *PlayerRoleString));
	
	APJEPlayerState* PJEPlayerState = Cast<APJEPlayerState>(NewPlayerState);
	if(PJEPlayerState)
	{
		PJEPlayerState->SetPlayerRole(this->PlayerRole);
	}
}
