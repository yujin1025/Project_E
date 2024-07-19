

#include "Items/DropItem.h"

#include "Character/PJECharacterPlayer.h"

ADropItem::ADropItem()
{
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetGenerateOverlapEvents(false);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();
}

void ADropItem::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	// 테스트로 일단 상호작용 키 누르면 ItemCode 전달하고 사라지게..
	if(Character)
	{
		Character->GetItem(ItemCode);
		Character->SetHandItemCode(ItemCode);
	}
	Destroy();
}