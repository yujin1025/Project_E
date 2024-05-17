

#include "Gimmick/PJEInteractiveActor.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
APJEInteractiveActor::APJEInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Interactive Actor"));
	RootComponent = SceneComponent;
	
	WidgetTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTriggerBox->SetupAttachment(RootComponent);
	InteractionTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	InteractionTriggerBox->SetupAttachment(RootComponent);

	DenoteInteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Denote Interaction Widget"));
	DenoteInteractionWidget->SetupAttachment(RootComponent);
	PointInteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Point Interaction WIdget"));
	PointInteractionWidget->SetupAttachment(RootComponent);
	
}

void APJEInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	DenoteInteractionWidget->SetVisibility(false);
	PointInteractionWidget->SetVisibility(false);
}

void APJEInteractiveActor::ShowDenoteInteractionWidget()
{
	DenoteInteractionWidget->SetVisibility(true);
}

void APJEInteractiveActor::HideDenoteInteractionWidget()
{
	DenoteInteractionWidget->SetVisibility(false);
}

void APJEInteractiveActor::ShowPointInteractionWidget()
{
	PointInteractionWidget->SetVisibility(true);
}

void APJEInteractiveActor::HidePointInteractionWidget()
{
	PointInteractionWidget->SetVisibility(false);
}

void APJEInteractiveActor::InteractionKeyPressed()
{
	if(!bIsInteractAble) return;
}

void APJEInteractiveActor::InteractionKeyReleased()
{
	if(!bIsInteractAble) return;
}

void APJEInteractiveActor::BreakInteracting()
{
}

void APJEInteractiveActor::AbleInteraction()
{
	bIsInteractAble = true;
}

void APJEInteractiveActor::DisableInteraction()
{
	bIsInteractAble = false;
	
	HidePointInteractionWidget();
	HideDenoteInteractionWidget();
}

void APJEInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

