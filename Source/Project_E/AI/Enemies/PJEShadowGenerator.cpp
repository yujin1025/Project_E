// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/PJECharacterShadow.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterShadowB.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AI/Enemies/PJEShadowArea.h"

// Sets default values
APJEShadowGenerator::APJEShadowGenerator()
{
    PrimaryActorTick.bCanEverTick = true;
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    bReplicates = true;
}

void APJEShadowGenerator::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        StartSpawnTimer();
    }
}

void APJEShadowGenerator::Server_SpawnMonster_Implementation(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation)
{
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // ������� �浹�� �����ϱ� ���� ����ĳ��Ʈ�� ����
    FHitResult HitResult;
    FVector StartLocation = DesiredLocation + FVector(0.0f, 0.0f, 500.0f); // ���� ��ġ ������ ����
    FVector EndLocation = DesiredLocation + FVector(0.0f, 0.0f, -500.0f); // ���� ��ġ �Ʒ��� ����ĳ��Ʈ
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params))
    {
        FVector SpawnLocation = HitResult.Location;

        // ���͸� ����
        APJECharacterShadow* SpawnedMonster = GetWorld()->SpawnActor<APJECharacterShadow>(MonsterClass, SpawnLocation, SpawnRotation);
        if (SpawnedMonster)
        {
            FVector BoundsExtent = SpawnedMonster->GetComponentsBoundingBox().GetExtent();
            SpawnLocation.Z += BoundsExtent.Z; // ���Ͱ� ���� ���� ��ġ�ϵ��� Z ���� ����
            SpawnedMonster->SetActorLocation(SpawnLocation);
            if (SpawnedMonster->IsA(APJECharacterShadowA::StaticClass()))
            {
                APJECharacterShadowA* ShadowA = Cast<APJECharacterShadowA>(SpawnedMonster);
                ShadowA->ShadowArea = ShadowArea;
                if(ShadowArea)
                {
                    ShadowArea->ShadowAArr.Add(ShadowA);
                }
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn monster at DesiredLocation."));
        }
    }
    else
    {
        // ����ĳ��Ʈ ���� ��
        UE_LOG(LogTemp, Warning, TEXT("Failed to find ground at DesiredLocation."));
    }
}


bool APJEShadowGenerator::Server_SpawnMonster_Validate(TSubclassOf<class APJECharacterShadow> MonsterClass, const FVector& DesiredLocation)
{
    return true;
}

void APJEShadowGenerator::Destroyed()
{
    if (ShadowArea)
    {
        ShadowArea->ShadowGeneratorArr.Remove(this);
        ShadowArea->SetBackgroundVolume(ShadowArea->ShadowGeneratorArr.Num());
    }
    Super::Destroyed();
}

void APJEShadowGenerator::StartSpawnTimer()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &APJEShadowGenerator::SpawnShadowAWithTimer, 10.0f, true);
}

void APJEShadowGenerator::SpawnShadowAWithTimer()
{
    for (int32 i = 0; i < 1; i++)
    {
        Server_SpawnMonster(ShadowBClass, SpawnPos);
        Server_SpawnMonster(ShadowAClass, SpawnPos);

        if (ShadowArea && ShadowArea->GetIsPlayerInArea())
        {
            ShadowArea->PlayShadowASound();
        }
    }
}

void APJEShadowGenerator::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
