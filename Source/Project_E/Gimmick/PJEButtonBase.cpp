// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEButtonBase.h"

#include "PJEPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APJEButtonBase::APJEButtonBase()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
	
	ButtonBorderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = ButtonBorderMesh;
	ButtonBorderMesh->SetGenerateOverlapEvents(false);
	
	ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	ButtonTrigger->SetupAttachment(RootComponent);
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(RootComponent);
	ButtonMesh->SetGenerateOverlapEvents(false);
	ButtonMesh->SetIsReplicated(true);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	Widget->SetupAttachment(RootComponent);

	WidgetTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APJEButtonBase::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = ButtonMesh->GetRelativeLocation();
	Widget->SetVisibility(false);
}

void APJEButtonBase::CheckButtonActive(float DeltaTime)
{
	//버튼의 이동은 서버에서만 일어난다.
	if(!HasAuthority()) return;
	
	FVector CurrentLocation = ButtonMesh->GetRelativeLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;

	if(FVector::Distance(CurrentLocation, TargetLocation) < 5.f)
	{
		if(bButtonActive == false)
		{
			NotifyActiveToPlatform(true);
		}
		bButtonActive = true;
	}
	else
	{
		if(bButtonActive == true)
		{
			NotifyActiveToPlatform(false);
		}
		bButtonActive = false;
	}
}

void APJEButtonBase::NotifyActiveToPlatform(bool ButtonActive)
{
	UE_LOG(LogTemp, Warning, TEXT("Now Button Active : %d"), ButtonActive);
	if(!Platforms.IsEmpty())
	{
		for(auto CurrentPlatform:Platforms)
		{
			CurrentPlatform->SetbPlatformActive(ButtonActive);
		}
	}
}

// Called every frame
void APJEButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckButtonActive(DeltaTime);
}

void APJEButtonBase::ShowInteractWidget()
{
	IPJEInteractInterface::ShowInteractWidget();

	Widget->SetVisibility(true);
}

void APJEButtonBase::HideInteractWidget()
{
	IPJEInteractInterface::HideInteractWidget();

	Widget->SetVisibility(false);
}

void APJEButtonBase::BeginInteracting(const AActor* InteractActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	IPJEInteractInterface::BeginInteracting(InteractActor);
}

void APJEButtonBase::EndInteracting(const AActor* InteractActor)
{
	IPJEInteractInterface::EndInteracting(InteractActor);
}
