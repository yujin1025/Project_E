

#include "Gimmick/BallFlower.h"

#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterDuck.h"

ABallFlower::ABallFlower()
{
	FlowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flower Mesh"));
	FlowerMesh->SetupAttachment(RootComponent);
}

void ABallFlower::BeginPlay()
{
	Super::BeginPlay();
}

void ABallFlower::InteractionKeyPressed(APJECharacterPlayer* Character)
{
	Super::InteractionKeyPressed(Character);

	// 상호작용하는 애니메이션 출력
	UAnimInstance* CharacterAnimInstance = Character->GetMesh()->GetAnimInstance();
	
	// 인벤토리에 공 추가
	Character->SetHandItemCode(ItemCode);
	
	if(APJECharacterDuck* DuckCharacter = Cast<APJECharacterDuck>(Character))
	{
		DuckCharacter->Swallow();
	}
	else if(APJECharacterCat* CatCharacter = Cast<APJECharacterCat>(Character))
	{
		CatCharacter->Grab();
	}
	
	Server_GetBall();
}

void ABallFlower::Server_GetBall_Implementation()
{
	NetMulticast_GetBall();
}

void ABallFlower::NetMulticast_GetBall_Implementation()
{
	// 공꽃 상호작용 불가능하게
	DisableInteraction();

	FlowerMesh->SetMaterial(3, TransparentMaterial);
}

