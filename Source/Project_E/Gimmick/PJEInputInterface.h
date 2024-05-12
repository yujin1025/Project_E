// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PJEInputInterface.generated.h"

class APJEPlayerController;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPJEInputInterface : public UInterface
{
	GENERATED_BODY()
};


class PROJECT_E_API IPJEInputInterface
{
	GENERATED_BODY()

public:
	virtual void SetupInputBinding(APJEPlayerController* PlayerController);
};
