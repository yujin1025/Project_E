// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DonutComponent.h"
#include "PrimitiveSceneProxy.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "SceneManagement.h"

UDonutComponent::UDonutComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    OuterRadius = 50.f;
    DonutHeight = 100.f;
    InnerRadius = 20.f;
}

FPrimitiveSceneProxy* UDonutComponent::CreateSceneProxy()
{
    Super::CreateSceneProxy();

    class FDonutSceneProxy : public FPrimitiveSceneProxy
    {
    public:
        FDonutSceneProxy(const UDonutComponent* InComponent)
            : FPrimitiveSceneProxy(InComponent)
            , OuterRadius(InComponent->OuterRadius)
            , DonutHeight(InComponent->DonutHeight)
            , InnerRadius(InComponent->InnerRadius)
        {
        }

        virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override
        {
            FPrimitiveSceneProxy::GetDynamicMeshElements(Views, ViewFamily, VisibilityMap, Collector);

            for (int32 ViewIndex = 0; ViewIndex < Views.Num(); ViewIndex++)
            {
                if (VisibilityMap & (1 << ViewIndex))
                {
                    FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
                    const FMatrix& LocalToWorld = GetLocalToWorld();

                    FVector Origin = LocalToWorld.GetOrigin();
                    FVector XAxis = LocalToWorld.GetScaledAxis(EAxis::X);
                    FVector YAxis = LocalToWorld.GetScaledAxis(EAxis::Y);
                    FVector ZAxis = LocalToWorld.GetScaledAxis(EAxis::Z);

                    // �ܰ� ���� �κ� �׸���
                    DrawWireCylinder(PDI, Origin, XAxis, YAxis, ZAxis, FLinearColor::Green, OuterRadius, DonutHeight / 2, 32, SDPG_World);

                    // �߾� �κ� �׸���
                    DrawWireCylinder(PDI, Origin, XAxis, YAxis, ZAxis, FLinearColor::Red, InnerRadius, DonutHeight / 2, 32, SDPG_World);
                }
            }
        }

        virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override
        {
            FPrimitiveViewRelevance Result = FPrimitiveSceneProxy::GetViewRelevance(View);
            Result.bDrawRelevance = IsShown(View);
            Result.bDynamicRelevance = true;
            Result.bShadowRelevance = IsShadowCast(View);
            Result.bStaticRelevance = false;
            // 빌드 시 에러
            /** 에러 내용
            * UATHelper: Packaging (Windows): D:\PJE\Project_E\Source\Project_E\Components\DonutComponent.cpp(67): error C2039: 'bNormalTranslucencyRelevance': 'FPrimitiveViewRelevance'의 멤버가 아닙니다.
            * UATHelper: Packaging (Windows): D:\PJE\Project_E\Source\Project_E\Components\DonutComponent.cpp(68): error C2039: 'bSeparateTranslucencyRelevance': 'FPrimitiveViewRelevance'의 멤버가 아닙니다.
            * UATHelper: Packaging (Windows): D:\PJE\Project_E\Source\Project_E\Components\DonutComponent.cpp(69): error C2039: 'bDistortionRelevance': 'FPrimitiveViewRelevance'의 멤버가 아닙니다.
            */ //아래 코드 3줄 주석처리
            // Result.bNormalTranslucencyRelevance = IsShown(View);
            // Result.bSeparateTranslucencyRelevance = IsShown(View);
            // Result.bDistortionRelevance = IsShown(View);
            Result.bEditorPrimitiveRelevance = IsSelected();
            Result.bRenderCustomDepth = ShouldRenderCustomDepth();
            Result.bMasked = false;
            Result.bTwoSided = false;

            return Result;
        }

        virtual bool CanBeOccluded() const override
        {
            FPrimitiveSceneProxy::CanBeOccluded();
            return true;
        }

        virtual uint32 GetMemoryFootprint() const override
        {
            return sizeof(*this) + GetAllocatedSize();
        }

        uint32 GetAllocatedSize() const
        {
            return FPrimitiveSceneProxy::GetAllocatedSize();
        }

        virtual SIZE_T GetTypeHash() const override
        {
            return FCrc::MemCrc32(this, sizeof(*this));
        }

    private:
        float OuterRadius;
        float DonutHeight;
        float InnerRadius;
    };

    return new FDonutSceneProxy(this);
}

FBoxSphereBounds UDonutComponent::CalcBounds(const FTransform& LocalToWorld) const
{
    Super::CalcBounds(LocalToWorld);

    FVector Origin = LocalToWorld.GetLocation();
    FVector Extent(OuterRadius, OuterRadius, DonutHeight / 2.0f);

    return FBoxSphereBounds(FBox(Origin - Extent, Origin + Extent));
}

bool UDonutComponent::IsPointInside(const FVector& Point) const
{
    FVector LocalPoint = GetComponentTransform().InverseTransformPosition(Point);
    float DistSquared = LocalPoint.X * LocalPoint.X + LocalPoint.Y * LocalPoint.Y;

    return (DistSquared <= OuterRadius * OuterRadius) && (FMath::Abs(LocalPoint.Z) <= DonutHeight / 2.0f) && !IsInsideInnerRadius(LocalPoint);
}

bool UDonutComponent::IsInsideInnerRadius(const FVector& LocalPoint) const
{
    float DistSquared = LocalPoint.X * LocalPoint.X + LocalPoint.Y * LocalPoint.Y;
    return DistSquared < InnerRadius * InnerRadius;
}
