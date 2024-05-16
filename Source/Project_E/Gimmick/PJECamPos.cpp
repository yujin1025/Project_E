// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJECamPos.h"

#include "Components/ArrowComponent.h"

// Sets default values
APJECamPos::APJECamPos()
{
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
}

FVector APJECamPos::GetArrowLocation() const
{
	return ArrowComponent->GetComponentLocation();
}

FRotator APJECamPos::GetArrowRotation() const
{
	return ArrowComponent->GetComponentRotation();
}

