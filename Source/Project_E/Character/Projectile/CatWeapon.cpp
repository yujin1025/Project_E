#include "CatWeapon.h"
#include "Components/BoxComponent.h"
#include "../PJECharacterBase.h"
#include "../PJECharacterPlayer.h"
#include "../PJECharacterCat.h"
#include "../PJECharacterDuck.h"
#include "../Component/HealthComponent.h"
#include "Components/WidgetComponent.h"

ACatWeapon::ACatWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &ACatWeapon::OnAttack);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ACatWeapon::BeginPlay()
{
    Super::BeginPlay();

}

void ACatWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    NotifyInteractionWidget->SetWorldLocation(CurrentLocation);
    PointInteractionWidget->SetWorldLocation(CurrentLocation);
    WidgetTriggerBox->SetWorldLocation(CurrentLocation);
    InteractionTriggerBox->SetWorldLocation(CurrentLocation);
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

void ACatWeapon::InteractionKeyPressed(APJECharacterPlayer* Character)
{
    Super::InteractionKeyPressed(Character);

    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Emerald, FString::Printf(TEXT("Get Projectile")));

    if (Character)
    {
        if (APJECharacterDuck* DuckCharacter = Cast<APJECharacterDuck>(Character))
        {
            if (ItemCode != 3)
            {
                Character->SetHandItemCode(ItemCode);
                DuckCharacter->Swallow();
                NetMulticast_Weapon();
            }
        }
        else if (APJECharacterCat* CatCharacter = Cast<APJECharacterCat>(Character))
        {
            if (ItemCode != 1)
            {
                Character->SetHandItemCode(ItemCode);
                if (CatCharacter->Grab())
                {
                    NetMulticast_Weapon();
                }
            }
        }
    }
}

void ACatWeapon::NetMulticast_Weapon_Implementation()
{
    Destroy();
}


