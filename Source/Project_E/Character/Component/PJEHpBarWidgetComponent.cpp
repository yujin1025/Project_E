// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PJEHpBarWidgetComponent.h"
#include "UI/PJEHealthBarWidget.h"
#include "Project_E/Character/Component/HealthComponent.h"

UPJEHpBarWidgetComponent::UPJEHpBarWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(TEXT("/Game/UI/WBP_PJEHealthBarWidget"));
    if (HealthBarWidgetClass.Succeeded())
    {
        HpBarWidgetClass = HealthBarWidgetClass.Class;
    }
}

TSubclassOf<class UUserWidget> UPJEHpBarWidgetComponent::GetHpBarWidgetClass()
{
    return HpBarWidgetClass;
}

void UPJEHpBarWidgetComponent::InitWidget()
{
    Super::InitWidget();

    UHealthComponent* HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();
    if (HealthComponent)
    {
        UPJEHealthBarWidget* HpBarWidget = Cast<UPJEHealthBarWidget>(GetUserWidgetObject());
        if (HpBarWidget)
        {
            HpBarWidget->SetHealthComponent(HealthComponent);
            HpBarWidget->UpdateHealthBar();
            HealthComponent->OnHealthChanged.BindUObject(HpBarWidget, &UPJEHealthBarWidget::UpdateHealthBar);
        }
    }
}
