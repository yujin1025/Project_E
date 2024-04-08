
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PJERotationPlatform.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_E_API UPJERotationPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPJERotationPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RotatePlatform(float Deltatime);

	FORCEINLINE void SetRotationOffset(int32 Offset) { RotationOffset = Offset; }
	
private:
	UPROPERTY(VisibleAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	int32 RotationOffset = 0;
	
	UPROPERTY(EditAnywhere, Category="Movement", meta=(AllowPrivateAccess = true))
	float RotationSpeed;

	UPROPERTY(VisibleAnywhere, Category="Movement")
	bool bInputActive;
};
