
#pragma once

#include "CoreMinimal.h"
#include "Game/PJEPlayerState.h"
#include "GameFramework/GameSession.h"
#include "LobbySession.generated.h"


enum class EPlayerRole : uint8;
class ULobbyWidget;

UCLASS()
class PROJECT_E_API ALobbySession : public AGameSession
{
	GENERATED_BODY()
public:
	ALobbySession();

	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdPtr& UniqueId, bool bWasFromInvite) override;
	virtual void UnregisterPlayer(const APlayerController* ExitingPlayer) override;

	void ChangeRole();
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	
	FDelegateHandle RegisterPlayerDelegateHandle;
	FDelegateHandle UnregisterPlayerDelegateHandle;
	
	void OnRegisterPlayerComplete(FName NameOfSession, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccessful);
	void OnUnregisterPlayerComplete(FName NameOfSession	, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccessful);

private:
	TArray<APlayerController*> PCs;

	ULobbyWidget* LobbyWidget;

	TArray<EPlayerRole> PlayerRoles {EPlayerRole::Cat, EPlayerRole::Duck};

public:
	void AddPC(APlayerController* PC) { PCs.Add(PC); }
	TArray<EPlayerRole> GetPlayerRoles() { return PlayerRoles; }
};
