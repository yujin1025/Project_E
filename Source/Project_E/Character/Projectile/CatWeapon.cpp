#include "CatWeapon.h"


ACatWeapon::ACatWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	ItemMesh->SetGenerateOverlapEvents(false);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACatWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ACatWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

