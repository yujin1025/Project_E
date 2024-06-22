// Fill out your copyright notice in the Description page of Project Settings.


#include "CrossHairWidget.h"
#include "Components/Image.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CanvasPanel.h>
#include "Engine/LocalPlayer.h"
#include "../Character/PJECharacterBase.h"
#include "../Player/PJEPlayerController.h"


void UCrossHairWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCrossHairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector2D NewScreenPosition = GetScreenMousePosition();
	SetPositionInViewport(NewScreenPosition);
}

FVector2D UCrossHairWidget::GetScreenMousePosition()
{
    APlayerController* PlayerController = GetOwningPlayer();
    if (PlayerController == nullptr)
        return FVector2D::ZeroVector;

    APJEPlayerController* Controller = Cast<APJEPlayerController>(PlayerController);
    if (Controller == nullptr)
        return FVector2D::ZeroVector;

    APJECharacterBase* Character = Cast<APJECharacterBase>(Controller->GetPawn());
    if (Character == nullptr)
        return FVector2D::ZeroVector;

    bool IsFoundTarget = false;
    FVector TargetLocation = Character->GetTargetPosition(ECollisionChannel::ECC_EngineTraceChannel1, 3500.0f, IsFoundTarget);

    FVector2D ScreenPosition;
    UGameplayStatics::ProjectWorldToScreen(PlayerController, TargetLocation, ScreenPosition);
    return ScreenPosition;
}

FVector2D UCrossHairWidget::GetAimScreenPosition(UImage* AimImage)
{
    if (!AimImage) return FVector2D::ZeroVector;

    // �θ� ������ Canvas Panel�� ã���ϴ�.
    UCanvasPanel* CanvasPanel = Cast<UCanvasPanel>(AimImage->GetParent());
    if (!CanvasPanel) return FVector2D::ZeroVector;

    // MyImage�� ���� ���� ��ġ�� �����ɴϴ�.
    FVector2D LocalPosition = AimImage->GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);

    // Canvas Panel�� ���� ���� ��ġ�� �����ɴϴ�.
    FVector2D CanvasPosition = CanvasPanel->GetCachedGeometry().LocalToAbsolute(FVector2D::ZeroVector);

    // MyImage�� ȭ�� ���� ��ġ�� ����մϴ�.
    FVector2D ScreenPosition = LocalPosition + CanvasPosition;

    return ScreenPosition;
}
