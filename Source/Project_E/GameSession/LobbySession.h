
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameSession.h"
#include "LobbySession.generated.h"


UCLASS()
class PROJECT_E_API ALobbySession : public AGameSession
{
	GENERATED_BODY()
public:
	ALobbySession();

	virtual void RegisterPlayer(APlayerController* NewPlayer, const FUniqueNetIdPtr& UniqueId, bool bWasFromInvite) override;
	virtual void UnregisterPlayer(const APlayerController* ExitingPlayer) override;
	
protected:
	virtual void BeginPlay() override;
	
	FDelegateHandle RegisterPlayerDelegateHandle;
	FDelegateHandle UnregisterPlayerDelegateHandle;
	
	void OnRegisterPlayerComplete(FName NameOfSession, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccessful);
	void OnUnregisterPlayerComplete(FName NameOfSession	, const TArray<FUniqueNetIdRef>& PlayerIds, bool bWasSuccessful);

private:
	TArray<APlayerController*> PCs;
};
