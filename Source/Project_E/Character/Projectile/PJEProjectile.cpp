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
	CollisionBox->BodyInstance.SetCollisionProfileName(TEXT("PJEProjectile"));
	CollisionBox->OnComponentHit.AddDynamic(this, &APJEProjectile::OnAttack);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionBox);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale; 
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
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

