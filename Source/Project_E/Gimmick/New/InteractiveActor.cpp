

#include "Gimmick/New/InteractiveActor.h"

#include "Components/WidgetComponent.h"

AInteractiveActor::AInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

	NotifyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Notify Widget"));
	NotifyWidget->SetupAttachment(RootComponent);
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);
}

void AInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

	NotifyWidget->SetVisibility(false);
	InteractionWidget->SetVisibility(false);

	// Default Settings
	bIsInteractAble = true;
	bIsInteracting = false;
	bIsActivate = false;
}

void AInteractiveActor::InteractionKeyPressed()
{
}

void AInteractiveActor::InteractionKeyReleased()
{
}

void AInteractiveActor::BreakInteracting()
{
	bIsInteracting = false;
}

void AInteractiveActor::DisplayNotifyWidget(bool bDisplay)
{
	NotifyWidget->SetVisibility(bDisplay);
}

void AInteractiveActor::DisplayInteractionWidget(bool bDisplay)
{
	InteractionWidget->SetVisibility(bDisplay);
}

void AInteractiveActor::SetInteraction(bool bCanInteract)
{
	if(bCanInteract)
	{
		bIsInteractAble = true;
	}
	else
	{
		bIsInteractAble = false;

		NotifyWidget->SetVisibility(false);
		InteractionWidget->SetVisibility(false);
	}
}
