// Fill out your copyright notice in the Description page of Project Settings.


#include "PJECharacterBase.h"

// Sets default values
APJECharacterBase::APJECharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APJECharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APJECharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APJECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

