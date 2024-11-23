// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShokeWave.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Component/HealthComponent.h"

APJEShockwave::APJEShockwave()
{
    PrimaryActorTick.bCanEverTick = true;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionSphere->SetupAttachment(RootComponent);
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APJEShockwave::OnOverlapBegin);
    CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APJEShockwave::OnOverlapEnd);

    InnerCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
    InnerCollisionSphere->SetupAttachment(CollisionSphere);
    InnerCollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    InnerCollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    
    InnerCollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APJEShockwave::OnInnerOverlapBegin);
    InnerCollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APJEShockwave::OnInnerOverlapEnd);

    DamagePerSec = 20.f;

    TimeElapsed = 0.0f;
}

void APJEShockwave::BeginPlay()
{
    Super::BeginPlay();

    Radius = CollisionSphere->GetScaledSphereRadius();
    InnerRadius = InnerCollisionSphere->GetScaledSphereRadius();
}

void APJEShockwave::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (APJECharacterPlayer* Player : OverlappingActors)
    {
        if (InnerOverlappingActors.Contains(Player) == false && Player->GetCharacterMovement()->IsMovingOnGround())
        {
            UGameplayStatics::ApplyDamage(Player, DamagePerSec * DeltaTime, nullptr, this, UDamageType::StaticClass());
        }
    }

    ExpandShokeWave(DeltaTime);
    DrawDebugSpheres();

    TimeElapsed += DeltaTime;
    if (ShokeWaveDuration < TimeElapsed)
    {
        Destroy();
    }
}

void APJEShockwave::DrawDebugSpheres()
{
    if (CollisionSphere && InnerCollisionSphere)
    {
        // ù ��° ���� �ݶ��̴��� ���� ����� ��
        DrawDebugSphere(
            GetWorld(),                                       // ���� ���ؽ�Ʈ
            CollisionSphere->GetComponentLocation(),          // ���� ��ġ
            CollisionSphere->GetScaledSphereRadius(),         // ���� �ݰ�
            24,                                               // ���׸�Ʈ ���� (���� �ػ�)
            FColor::Red,                                      // ����
            false,                                            // ���� ���� (false: ���� �ð� �� �����)
            -1.0f,                                            // ���� �ð� (��, -1: ����)
            0,                                                // ����� ���� �켱 ����
            2.0f                                              // �β�
        );

        // �� ��° ���� �ݶ��̴��� ���� ����� ��
        DrawDebugSphere(
            GetWorld(),
            InnerCollisionSphere->GetComponentLocation(),
            InnerCollisionSphere->GetScaledSphereRadius(),
            24,
            FColor::Green,
            false,
            -1.0f,
            0,
            2.0f
        );
    }
}

void APJEShockwave::ExpandShokeWave(float DeltaTime)
{
    Radius += DeltaTime * ExpandSpeed;
    InnerRadius += DeltaTime * ExpandSpeed;

    CollisionSphere->SetSphereRadius(Radius);
    InnerCollisionSphere->SetSphereRadius(InnerRadius);

}

void APJEShockwave::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (APJECharacterPlayer* Player = Cast<APJECharacterPlayer>(OtherActor))
    {
        OverlappingActors.Add(Player);
    }
}

void APJEShockwave::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (APJECharacterPlayer* Player = Cast<APJECharacterPlayer>(OtherActor))
    {
        OverlappingActors.Remove(Player);
    }
}

void APJEShockwave::OnInnerOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (APJECharacterPlayer* Player = Cast<APJECharacterPlayer>(OtherActor))
    {
        InnerOverlappingActors.Add(Player);
    }
}

void APJEShockwave::OnInnerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (APJECharacterPlayer* Player = Cast<APJECharacterPlayer>(OtherActor))
    {
        InnerOverlappingActors.Remove(Player);
    }
}