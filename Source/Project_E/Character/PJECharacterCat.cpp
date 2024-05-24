// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Triggered, this, &APJECharacterCat::Swing);
    }
}


void APJECharacterCat::BeginPlay()
{
    Super::BeginPlay();

}


void APJECharacterCat::Grab()
{
    Super::Grab();

}

void APJECharacterCat::Swing()
{
}

void APJECharacterCat::Dash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= DashSpeed;
    }
}
