// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJEButtonBase.h"

#include "PJEPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APJEButtonBase::APJEButtonBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ButtonBorderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button Boarder"));
	RootComponent = ButtonBorderMesh;
	ButtonBorderMesh->SetGenerateOverlapEvents(false);
	
	ButtonTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	ButtonTrigger->SetupAttachment(RootComponent);
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	ButtonMesh->SetupAttachment(RootComponent);
	ButtonMesh->SetGenerateOverlapEvents(false);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	Widget->SetupAttachment(ButtonMesh);

}

// Called when the game starts or when spawned
void APJEButtonBase::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = ButtonMesh->GetRelativeLocation();
	Widget->SetVisibility(false);
}

void APJEButtonBase::MoveButton(float DeltaTime)
{
	FVector CurrentLocation = ButtonMesh->GetRelativeLocation();
	FVector TargetLocation = OriginLocation + MoveOffset;
	float Speed = FVector::Distance(OriginLocation, TargetLocation) / MoveTime;

	// Interactive 여부에 따라 버튼을 임계점이나 원 위치로 움직이게 한다
	if(bButtonInteract)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Button Active"));
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}
	else
	{
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, OriginLocation, DeltaTime, Speed);
		ButtonMesh->SetRelativeLocation(NewLocation);
	}

	// Button이 임계점까지 움직이면 bButtonActive를 true로 변경
	// ButtonActive 상태가 변경되면 Platform으로 Notify 보낸다
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
	Platforms[0]->SetbPlatformActive(ButtonActive);
}

// Called every frame
void APJEButtonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
