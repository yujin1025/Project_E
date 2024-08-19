// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PJEHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UPJEHealthBarWidget::UpdateHealthBar(float CurrentHealth, float MaxHealth)
{
    if (HealthProgressBar)
    {
        float HealthPercent = CurrentHealth / MaxHealth;
        HealthProgressBar->SetPercent(HealthPercent);
    }
}