
#include "Gimmick/PJERotateComponent.h"

UPJERotateComponent::UPJERotateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPJERotateComponent::OperateRotation()
{
	
}

void UPJERotateComponent::StopRotation()
{
}

void UPJERotateComponent::ResetRotation()
{
}

FRotator UPJERotateComponent::RNewInterpConstantTo(const FRotator& Current, const FRotator& Target, float DeltaTime,
	float InterpSpeed)
{
	FRotator NewRotation = Current;
	bool bClockwise = true;

	if(InterpSpeed < 0)
	{
		InterpSpeed = -InterpSpeed;
		bClockwise = false; 
	}

	for(int32 Axis = 0; Axis < 3; Axis++)
	{
		float CurrentAngle = Current.Euler()[Axis];
		float TargetAngle = Target.Euler()[Axis];
		float Step;
		
		float Difference = FMath::UnwindDegrees(TargetAngle - CurrentAngle);

		if(bClockwise)
		{
			if(Difference < 0)
			{
				Difference += 360.f;
			}
			Step = FMath::Min(Difference, InterpSpeed * DeltaTime);
		}
		else
		{
			if(Difference > 0)
			{
				Difference -= 360.f;
			}
			Step = FMath::Max(Difference, -InterpSpeed*DeltaTime);
		}
		NewRotation.SetComponentForAxis((EAxis::Type)Axis, FMath::UnwindDegrees(CurrentAngle + Step));
	}
	return NewRotation;
}


void UPJERotateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPJERotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

