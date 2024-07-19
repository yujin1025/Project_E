// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../PJECharacterBase.h"
#include "../Component/HealthComponent.h"

APJEProjectile::APJEProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	CollisionBox->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionBox->OnComponentHit.AddDynamic(this, &APJEProjectile::OnAttack);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionBox);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale; //38.445 % 9.8
	ProjectileMovementComponent->bShouldBounce = false; 
}


void APJEProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void APJEProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();

	// 디버그 스피어 그리기
	DrawDebugSphere(GetWorld(), CurrentLocation, 10.0f, 12, FColor::Green, false, -1.0f, 0, 1.0f);

}

void APJEProjectile::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APJECharacterBase* DamagedCharacter = Cast<APJECharacterBase>(OtherActor);
	if (DamagedCharacter)
	{
		UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
		if (DamagedHealthComponent == nullptr)
			return;

		DamagedHealthComponent->ChangeHealth(-10);
		Destroy();
	}

}

