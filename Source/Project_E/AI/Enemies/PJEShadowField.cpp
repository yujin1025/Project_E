// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowField.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "Character/PJECharacterPlayer.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

// Sets default values
APJEShadowField::APJEShadowField()
{
    PrimaryActorTick.bCanEverTick = true;

    bReplicates = true;

    // Collision sphere
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(100.0f);
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));  // 트리거로 설정
    SetRootComponent(CollisionSphere);

    // Field mesh
    FieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FieldMesh"));
    FieldMesh->SetupAttachment(RootComponent);

    NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    NiagaraComponent->SetupAttachment(RootComponent);

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &APJEShadowField::OnOverlapBegin);
    CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &APJEShadowField::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APJEShadowField::BeginPlay()
{
    Super::BeginPlay();

    if (NiagaraComponent && NiagaraComponent->GetAsset())
    {
        NiagaraComponent->Activate(true);
    }
}

// Called every frame
void APJEShadowField::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;
    if (TimeElapsed > FieldDuration)
    {
        Destroy();
    }
    else
    {
        ShrinkField(DeltaTime);

        // 겹쳐진 액터에게 지속적인 데미지
        for (AActor* Actor : OverlappingActors)
        {
            if (Actor && Actor->IsA(APJECharacterPlayer::StaticClass()))
            {
                UGameplayStatics::ApplyDamage(Actor, DamagePerSecond * DeltaTime, nullptr, this, UDamageType::StaticClass());
            }
        }
    }
}

void APJEShadowField::InitializeField(float Duration, float Damage, float InitialRadius)
{
    FieldDuration = Duration;
    DamagePerSecond = Damage;
    FieldRadius = InitialRadius;
}

void APJEShadowField::ShrinkField(float DeltaTime)
{
    // 현재 시간이 경과한 전체 지속 시간의 비율에 따라 축소 팩터 계산
    float ShrinkFactor = FMath::Clamp(1.0f - (TimeElapsed / FieldDuration), 0.0f, 1.0f) * FieldRadius;
    SetActorScale3D(FVector(ShrinkFactor));
}


void APJEShadowField::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APJECharacterPlayer::StaticClass()))
    {
        OverlappingActors.Add(OtherActor); // 겹쳐진 액터를 배열에 추가
    }
}

void APJEShadowField::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->IsA(APJECharacterPlayer::StaticClass()))
    {
        OverlappingActors.Remove(OtherActor); // 겹침이 끝난 액터를 배열에서 제거
    }
}
