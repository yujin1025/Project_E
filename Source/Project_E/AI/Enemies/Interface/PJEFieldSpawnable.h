// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PJEFieldSpawnable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPJEFieldSpawnable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECT_E_API IPJEFieldSpawnable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetFieldRadius() = 0;
	virtual float GetFieldDuration() = 0;
	virtual float GetDamagePerSecond() = 0;
	virtual void SetFieldActor(class APJEShadowField* NewFieldActor) = 0;
	virtual class APJEShadowField* GetFieldActor() = 0;

protected:
	virtual void DestoryField(AActor* DestroyedActor) = 0;
};
