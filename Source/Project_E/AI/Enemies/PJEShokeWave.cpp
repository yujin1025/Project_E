// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShokeWave.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

APJEShokeWave::APJEShokeWave()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DonutComponent"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APJEShokeWave::OnOverlapBegin);

    DamageAmount = 20.f;
}

void APJEShokeWave::BeginPlay()
{
    Super::BeginPlay();
}

void APJEShokeWave::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APJEShokeWave::ExpandShokeWave(float DeltaTime)
{
}

void APJEShokeWave::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
}

void APJEShokeWave::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


