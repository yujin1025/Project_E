

#include "Gimmick/PJEInteractiveActor.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


APJEInteractiveActor::APJEInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Interactive Actor"));
	RootComponent = SceneComponent;
	
	WidgetTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTriggerBox->SetupAttachment(RootComponent);
	InteractionTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Trigger"));
	InteractionTriggerBox->SetupAttachment(RootComponent);

	NotifyInteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Denote Interaction Widget"));
	NotifyInteractionWidget->SetupAttachment(RootComponent);
	PointInteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Point Interaction WIdget"));
	PointInteractionWidget->SetupAttachment(RootComponent);
}

void APJEInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	NotifyInteractionWidget->SetVisibility(false);
	PointInteractionWidget->SetVisibility(false);

	//Default Settings
	bIsInteractAble = true;
	bIsInteracting = false;
	bIsActive = false;
	InteractType = EInteractType::Click;
}

/* Functions that contain functionality to act when an interaction key is pressed **/
void APJEInteractiveActor::InteractionKeyPressed()
{
	if(!bIsInteractAble) return;
}
/* Functions that contain functionality to act when an interaction key is released **/
void APJEInteractiveActor::InteractionKeyReleased()
{
	if(!bIsInteractAble) return;
}

/* Break Interacting **/
void APJEInteractiveActor::BreakInteracting()
{
	bIsInteracting = false;
}

/* Actor ready to Interact.. default setting **/
void APJEInteractiveActor::AbleInteraction()
{
	bIsInteractAble = true;
}

/* Actor now unable to interact
 * Hide all interaction widgets
 * Set actor interaction disabled **/
void APJEInteractiveActor::DisableInteraction()
{
	bIsInteractAble = false;

	NotifyInteractionWidget->SetVisibility(false);
	PointInteractionWidget->SetVisibility(false);
}

/* Update Widget **/
void APJEInteractiveActor::UpdateWidget()
{
	if(!bIsInteractAble) return;
	
	TArray<AActor*> NotifyOverlappingActors, PointOverlappingActors;
	WidgetTriggerBox->GetOverlappingActors(NotifyOverlappingActors);
	if(NotifyOverlappingActors.Num() == 0)
	{
		NotifyInteractionWidget->SetVisibility(false);
	}
	else
	{
		NotifyInteractionWidget->SetVisibility(true);
	}

	InteractionTriggerBox->GetOverlappingActors(PointOverlappingActors);
	if(PointOverlappingActors.Num() == 0)
	{
		PointInteractionWidget->SetVisibility(false);
	}
	else
	{
		PointInteractionWidget->SetVisibility(true);
	}
}

void APJEInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWidget();
}

