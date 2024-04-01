// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"
#include "Interface/PJECharacterItemInterface.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh"));
	SetRootComponent(ItemMesh);
	ItemMesh->SetGenerateOverlapEvents(false);
	
	WidgetTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTrigger->SetupAttachment(ItemMesh);

	Item = NewObject<UItem>(this, TEXT("Item"));
}


// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::SetItem(const FString& ItemName)
{
    UDataTable* ItemDatabase = LoadObject<UDataTable>(nullptr, TEXT("/Game/Data/itemData.itemData"));
    if (ItemDatabase)
    {
        FItemData* ItemData = ItemDatabase->FindRow<FItemData>(*ItemName, TEXT(""));

        if (ItemData)
        {
            //Item->Name = ItemData->Name;
            //Item->Type = ItemData->Type;
            //Item->Weight = ItemData->Weight;
            //Item->Damage = ItemData->Damage;

            //UE_LOG(LogTemp, Warning, TEXT("Item Name: %s"), *Item->Name);
            //UE_LOG(LogTemp, Warning, TEXT("Item Type: %d"), static_cast<int32>(Item->Type));
            //UE_LOG(LogTemp, Warning, TEXT("Item Weight: %f"), Item->Weight);
            //UE_LOG(LogTemp, Warning, TEXT("Item Damage: %f"), Item->Damage);
        }
    }
}