

#include "Gimmick/New/InteractiveActor.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"

AInteractiveActor::AInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Interactive Actor"));
	RootComponent = Root;
	
	NotifyWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Notify Widget"));
	NotifyWidget->SetupAttachment(RootComponent);
	NotifyWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Interaction Widget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);
}

void AInteractiveActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInteractiveActor, ControlPawn);
	DOREPLIFETIME(AInteractiveActor, bIsInteractAble);
	DOREPLIFETIME(AInteractiveActor, bIsInteracting);
	DOREPLIFETIME(AInteractiveActor, bIsActivate);
}

void AInteractiveActor::InteractionKeyPressed()
{
}

void AInteractiveActor::InteractionKeyReleased()
{
}

void AInteractiveActor::BreakInteracting()
{
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
