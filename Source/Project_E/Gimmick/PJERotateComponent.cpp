
#include "Gimmick/PJERotateComponent.h"

UPJERotateComponent::UPJERotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPJERotateComponent::OperateRotation(float DeltaTime)
{
	FRotator CurrentRotator = GetOwner()->GetActorRotation();
	FRotator NewRotator = CurrentRotator + RotationAngle * DeltaTime * RotationSpeed;

	const FQuat Quat1 = FQuat(NewRotator);
	const FQuat Quat2 = FQuat(OriginRotation);
	float AngleRadian = Quat1.AngularDistance(Quat2);
	float AngleDegree = FMath::RadiansToDegrees(AngleRadian);

	if(AngleDegree > MaxRotateDegree)
	{
		return;
	}
	GetOwner()->SetActorRotation(NewRotator);
}

void UPJERotateComponent::StopRotation()
{

}

void UPJERotateComponent::ResetRotation(float DeltaTime)
{
	FRotator CurrentRotator = GetOwner()->GetActorRotation();
	float Speed = FMath::Abs(RotationSpeed);
	FRotator NewRotation = FMath::RInterpConstantTo(CurrentRotator, OriginRotation, DeltaTime, Speed);
	GetOwner()->SetActorRotation(NewRotation);
}

void UPJERotateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OriginRotation = GetOwner()->GetActorRotation();
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

