#include "Items/DropItem.h"
#include "Character/PJECharacterPlayer.h"
#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"

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

	if(Character)
	{
		if (APJECharacterDuck* DuckCharacter = Cast<APJECharacterDuck>(Character))
		{
			if (ItemCode != 3)
			{
				Character->SetHandItemCode(ItemCode);

				if (HasAuthority())  
				{
					DuckCharacter->Swallow();
				}
				else
				{
					DuckCharacter->Server_Swallow();
				}

				Destroy();
			}
		}
		else if (APJECharacterCat* CatCharacter = Cast<APJECharacterCat>(Character))
		{
			if (ItemCode != 1)
			{
				Character->SetHandItemCode(ItemCode);

				if (HasAuthority()) 
				{
					if (CatCharacter->Grab())
					{
						Destroy();
					}
				}
				else
				{
					CatCharacter->Server_Grab();
				}
			}
		}
	}
	
}
