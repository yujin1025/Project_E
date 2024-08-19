// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShokeWave.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DonutComponent.h"

APJEShokeWave::APJEShokeWave()
{
    PrimaryActorTick.bCanEverTick = true;

    DonutComponent = CreateDefaultSubobject<UDonutComponent>(TEXT("DonutComponent"));
    DonutComponent->SetupAttachment(RootComponent);
    DonutComponent->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    DonutComponent->SetCollisionProfileName(TEXT("Trigger"));
    DonutComponent->OnComponentBeginOverlap.AddDynamic(this, &APJEShokeWave::OnOverlapBegin);

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

void APJEShokeWave::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        FVector OtherActorLocation = OtherActor->GetActorLocation();

        if (DonutComponent->IsPointInside(OtherActorLocation))
        {
            UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetInstigatorController(), this, nullptr);
        }
    }
}


