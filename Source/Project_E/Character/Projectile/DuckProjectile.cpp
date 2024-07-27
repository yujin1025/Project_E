// Fill out your copyright notice in the Description page of Project Settings.


#include "DuckProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/PJECharacterPlayer.h"
#include "Character/PJECharacterBase.h"
#include "../Component/HealthComponent.h"
#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

ADuckProjectile::ADuckProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionComponent);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("PJEProjectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &ADuckProjectile::OnAttack);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(CollisionComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->ProjectileGravityScale = GravityScale;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f; 
	ProjectileMovementComponent->BounceVelocityStopSimulatingThreshold = 500.0f;
}

void ADuckProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ADuckProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	NotifyInteractionWidget->SetWorldLocation(CurrentLocation);
	PointInteractionWidget->SetWorldLocation(CurrentLocation);
	WidgetTriggerBox->SetWorldLocation(CurrentLocation);
	InteractionTriggerBox->SetWorldLocation(CurrentLocation);
}

void ADuckProjectile::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComp->IsSimulatingPhysics())
	{
		APJECharacterBase* DamagedCharacter = Cast<APJECharacterBase>(OtherActor);
		if (DamagedCharacter)
		{
			UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent == nullptr)
				return;

			UE_LOG(LogTemp, Warning, TEXT("Projectile OnAttack"));
			DamagedHealthComponent->ChangeHealth(-10);
		}
	}

}

void ADuckProjectile::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	if (Character)
	{
		Character->SetHandItemCode(ItemCode);

		if (APJECharacterDuck* DuckCharacter = Cast<APJECharacterDuck>(Character))
		{
			DuckCharacter->Swallow();
		}
		else if (APJECharacterCat* CatCharacter = Cast<APJECharacterCat>(Character))
		{
			CatCharacter->Grab();
		}
	}
	Destroy();
}
