// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Component/PJEHpBarWidgetComponent.h"
#include "Blueprint/UserWidget.h"

UPJEHpBarWidgetComponent::UPJEHpBarWidgetComponent()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(TEXT("/Game/UI/WBP_PJEHealthBarWidget"));
    if (HealthBarWidgetClass.Succeeded())
    {
        HpBarWidgetClass = HealthBarWidgetClass.Class;
    }
}
