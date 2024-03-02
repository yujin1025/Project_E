// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Interface/PJECharacterItemInterface.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Bind to the overlap event
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnOverlapBegin);
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

void AItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//Cast to CharacterItemInterface
	IPJECharacterItemInterface* OverlappingPawn = Cast<IPJECharacterItemInterface>(OtherActor);
	if (OverlappingPawn)
	{
		//OverlappingPawn->TakeItem(Item);
	}
}