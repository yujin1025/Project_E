#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SwitchTarget.generated.h"

UCLASS()
class PROJECT_E_API UBTTask_SwitchTarget : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UBTTask_SwitchTarget();

protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
    AActor* GetRandomPlayerActor(const TArray<AActor*>& Players, AActor* CurrentTarget);
};
