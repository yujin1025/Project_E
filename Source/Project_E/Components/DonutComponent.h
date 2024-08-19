// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "DonutComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECT_E_API UDonutComponent : public UPrimitiveComponent
{
    GENERATED_BODY()

public:
    UDonutComponent();

protected:
    virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut")
    float OuterRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut")
    float DonutHeight;

    // 중앙 영역의 반지름
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Donut")
    float InnerRadius;

    virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;
    virtual bool IsPointInside(const FVector& Point) const;

private:
    bool IsInsideInnerRadius(const FVector& LocalPoint) const;
	
};


