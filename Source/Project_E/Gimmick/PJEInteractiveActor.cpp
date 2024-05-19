

#include "Gimmick/PJEInteractiveActor.h"

#include "Character/PJECharacterPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"


APJEInteractiveActor::APJEInteractiveActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Interactive Actor"));
	RootComponent = Root;
	
	WidgetTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Widget Trigger"));
	WidgetTriggerBox->SetupAttachment(RootComponent);
	WidgetTriggerBox->SetCollisionProfileName(TEXT("NotifyInteraction"));
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

	WidgetTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APJEInteractiveActor::OnOverlapBegin);
	WidgetTriggerBox->OnComponentEndOverlap.AddDynamic(this, &APJEInteractiveActor::OnOverlapEnd);
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

void APJEInteractiveActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APJECharacterPlayer* CharacterPlayer = Cast<APJECharacterPlayer>(OtherActor);
	if(CharacterPlayer)
	{
		NotifyInteractionWidget->SetVisibility(true);
	}
}

void APJEInteractiveActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APJECharacterPlayer* CharacterPlayer = Cast<APJECharacterPlayer>(OtherActor);
	if(CharacterPlayer)
	{
		NotifyInteractionWidget->SetVisibility(false);
	}
}

void APJEInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

