

#include "Gimmick/PJEMovingComponent.h"

UPJEMovingComponent::UPJEMovingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MovementState = EMovementState::Interrupt;
}


// Called when the game starts
void UPJEMovingComponent::BeginPlay()
{
	Super::BeginPlay();

	if(MovementTarget)
	{
		OriginLocation = MovementTarget->GetComponentLocation();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Movement Target"));
	}
}

void UPJEMovingComponent::OperateMove(float DeltaTime)
{
	
	FVector CurrentLocation = MovementTarget->GetComponentLocation();
	FVector TargetLocation = OriginLocation + MovementOffset;
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, MovementSpeed);
	MovementTarget->SetWorldLocation(NewLocation);
	
	if(GEngine) GEngine->AddOnScreenDebugMessage(90, 10.f, FColor::Emerald, FString::Printf(TEXT("Current Location : %s"), *CurrentLocation.ToString()));
	
	if(FVector::Distance(CurrentLocation, TargetLocation) < 1.f)
	{
		bIsArrived = true;
	}
}

void UPJEMovingComponent::StopMove()
{
}

void UPJEMovingComponent::ResetMove(float DeltaTime)
{
	bIsArrived = false;

	FVector CurrentLocation = MovementTarget->GetComponentLocation();
	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, MovementSpeed);
	MovementTarget->SetWorldLocation(NewLocation);
}


void UPJEMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	switch(MovementState)
	{
	case EMovementState::Moving:
		OperateMove(DeltaTime);
		break;
	case EMovementState::Interrupt:
		StopMove();
		break;
	case EMovementState::Returning:
		ResetMove(DeltaTime);
		break;
	}
}

