#include "DropItem.h"
#include "Character/PJECharacterPlayer.h"
#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"
#include "Components/WidgetComponent.h"
#include "Components/BoxComponent.h"

ADropItem::ADropItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	ItemMesh->SetupAttachment(RootComponent);
	//ItemMesh->SetGenerateOverlapEvents(false);
	//ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetReplicates(true);
	SetReplicateMovement(true);
}

void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation = GetActorLocation();
	NotifyInteractionWidget->SetWorldLocation(CurrentLocation);
	PointInteractionWidget->SetWorldLocation(CurrentLocation);
	WidgetTriggerBox->SetWorldLocation(CurrentLocation);
	InteractionTriggerBox->SetWorldLocation(CurrentLocation);
}

void ADropItem::BeginPlay()
{
	Super::BeginPlay();
}

void ADropItem::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	if(Character)
	{
		if (APJECharacterDuck* DuckCharacter = Cast<APJECharacterDuck>(Character))
		{
			if (ItemCode != 3)
			{
				Character->SetHandItemCode(ItemCode);
				DuckCharacter->Swallow();
				Destroy();
			}
		}
		else if (APJECharacterCat* CatCharacter = Cast<APJECharacterCat>(Character))
		{
			if (ItemCode != 1)
			{
				Character->SetHandItemCode(ItemCode);
				if (CatCharacter->Grab())
					Destroy();
			}
		}
	}
}
