#include "Gimmick/PJEPushableCylinder.h"

APJEPushableCylinder::APJEPushableCylinder()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APJEPushableCylinder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APJEPushableCylinder::BeginPlay()
{
	Super::BeginPlay();
	
}

void APJEPushableCylinder::ReturnPawnInput()
{
}

void APJEPushableCylinder::InteractionKeyReleased(APJECharacterPlayer* Character)
{
	Super::InteractionKeyReleased(Character);
}

void APJEPushableCylinder::InitInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	
}

