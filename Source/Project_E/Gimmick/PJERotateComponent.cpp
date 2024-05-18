
#include "Gimmick/PJERotateComponent.h"

UPJERotateComponent::UPJERotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPJERotateComponent::OperateRotation(float DeltaTime)
{
	if(!RotateTarget) return;
	FRotator CurrentRotator = RotateTarget->GetComponentRotation();
	FRotator NewRotator = CurrentRotator + RotationAngle * DeltaTime * RotationSpeed;

	const FQuat Quat1 = FQuat(NewRotator);
	const FQuat Quat2 = FQuat(OriginRotation);
	float AngleRadian = Quat1.AngularDistance(Quat2);
	float AngleDegree = FMath::RadiansToDegrees(AngleRadian);
	if(AngleDegree > MaxRotateDegree)
	{
		return;
	}
	
	RotateTarget->SetWorldRotation(NewRotator);
}

void UPJERotateComponent::StopRotation()
{

}

void UPJERotateComponent::ResetRotation(float DeltaTime)
{
	if(!RotateTarget) return;
	
	FRotator CurrentRotator = RotateTarget->GetComponentRotation();
	float Speed = FMath::Abs(RotationSpeed);
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotator, OriginRotation, DeltaTime, Speed);
	RotateTarget->SetWorldRotation(NewRotation);
}

void UPJERotateComponent::BeginPlay()
{
	Super::BeginPlay();

	if(RotateTarget)
	{
		OriginRotation = RotateTarget->GetComponentRotation();
	}
}

void UPJERotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (RotateState)
	{
	case ERotateState::Rotating:
		OperateRotation(DeltaTime);
		break;
	case ERotateState::Interrupt:
		StopRotation();
		break;
	case ERotateState::Returning:
		ResetRotation(DeltaTime);
		break;
	}
}

