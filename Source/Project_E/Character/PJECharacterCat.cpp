// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterCat.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PJEPlayerController.h"


APJECharacterCat::APJECharacterCat()
{
}

void APJECharacterCat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
        PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &APJECharacterCat::DoubleJump);
        PlayerInputComponent->BindAction(FName("Dash"), IE_Pressed, this, &APJECharacterCat::Dash);
        PlayerInputComponent->BindAction(FName("Dash"), IE_Released, this, &APJECharacterCat::StopDash);
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
    JumpCount = 0;
}

void APJECharacterCat::DoubleJump()
{
    if (bFirstJump)
    {
        bFirstJump = false;
        JumpCount++;
        Jump();
    }
    else if (!bFirstJump && JumpCount < 2)
    {
        UCharacterMovementComponent* PlayerMovement = GetCharacterMovement();
        if (PlayerMovement)
        {
            FVector Start = GetActorUpVector();
            float DefaultJumpHeight = PlayerMovement->JumpZVelocity;
            FVector End = GetActorLocation() + Start * DefaultJumpHeight;
            LaunchCharacter(End - GetActorLocation(), false, true);
            JumpCount++;
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

void APJECharacterCat::StopDash()
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
    }
}

void APJECharacterCat::Attack()
{
    Super::Attack();

}

void APJECharacterCat::Swing()
{
}