// Fill out your copyright notice in the Description page of Project Settings.


#include "PJEProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../PJECharacterBase.h"
#include "../Component/HealthComponent.h"

APJEProjectile::APJEProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("PJEProjectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &APJEProjectile::OnAttack);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale; 
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	//InitialLifeSpan = 10.0f; 
}


void APJEProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void APJEProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	}

}

