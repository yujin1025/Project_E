// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEHealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Project_E/Character/Component/HealthComponent.h"

void UPJEHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UPJEHealthBarWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        float HealthPercent = HealthComponent->GetCurrentHealth() / HealthComponent->GetMaxHealth();
        HealthProgressBar->SetPercent(HealthPercent);
    }
}

void UPJEHealthBarWidget::SetHealthComponent(UHealthComponent* NewHealthComponent)
{
    HealthComponent = NewHealthComponent;
}
