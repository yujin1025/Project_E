// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"

APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &APJECharacterCat::DoubleJump);
        PlayerInputComponent->BindAction(FName("Dash"), IE_Pressed, this, &APJECharacterCat::Dash);
    }
}

void APJECharacterCat::BeginPlay()
{
    Super::BeginPlay();
}

void APJECharacterCat::Landed(const FHitResult& Hit)
{
    Super::Landed(Hit);
    bFirstJump = true;
}

void APJECharacterCat::DoubleJump()
{
    if (bFirstJump)
    {
        bFirstJump = false;
        Jump();
    }
    else
    {
        UCharacterMovementComponent* PlayerMovement = GetCharacterMovement();
        if (PlayerMovement)
        {
            FVector Start = GetActorUpVector();
            float DefaultJumpHeight = PlayerMovement->JumpZVelocity;
            FVector End = GetActorLocation() + Start * DefaultJumpHeight;
            LaunchCharacter(End - GetActorLocation(), false, true);
        }
    }
}

void APJECharacterCat::Dash()
{
    //const FVector Direction = GetActorRotation().Vector();
    //LaunchCharacter(Direction * DashDistance, true, true);
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
    }
}

void APJECharacterCat::Attack()
{
    Super::Attack();

}

void APJECharacterCat::Swing()
{
}