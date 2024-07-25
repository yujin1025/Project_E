#include "CatWeapon.h"
#include "Components/BoxComponent.h"
#include "../PJECharacterBase.h"
#include "../Component/HealthComponent.h"

ACatWeapon::ACatWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ACatWeapon::OnAttack);

	SetReplicates(true);
}

void ACatWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACatWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACatWeapon::SetDamage(float Damage)
{
	DamageAmount = Damage;
}

void ACatWeapon::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APJECharacterBase* DamagedCharacter = Cast<APJECharacterBase>(OtherActor);
	if (DamagedCharacter)
	{
		UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
		if (DamagedHealthComponent == nullptr)
			return;

		DamagedHealthComponent->ChangeHealth(-DamageAmount);
	}
}


