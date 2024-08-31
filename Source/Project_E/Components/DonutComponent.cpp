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
                // ViewIndex와 VisibilityMap의 비트 연산 검사
                if ((VisibilityMap & (1 << ViewIndex)) != 0)
                {
                    if (ViewIndex >= 0 && ViewIndex < Views.Num()) // 인덱스가 배열 크기 내에 있는지 다시 확인
                    {
                        FPrimitiveDrawInterface* PDI = Collector.GetPDI(ViewIndex);
                        const FMatrix& LocalToWorld = GetLocalToWorld();

                        FVector Origin = LocalToWorld.GetOrigin();
                        FVector XAxis = LocalToWorld.GetScaledAxis(EAxis::X);
                        FVector YAxis = LocalToWorld.GetScaledAxis(EAxis::Y);
                        FVector ZAxis = LocalToWorld.GetScaledAxis(EAxis::Z);

                        // 외부 실린더 그리기
                        DrawWireCylinder(PDI, Origin, XAxis, YAxis, ZAxis, FLinearColor::Green, OuterRadius, DonutHeight / 2, 32, SDPG_World);

                        // 내부 실린더 그리기
                        DrawWireCylinder(PDI, Origin, XAxis, YAxis, ZAxis, FLinearColor::Red, InnerRadius, DonutHeight / 2, 32, SDPG_World);
                    }
                    else
                    {
                        UE_LOG(LogTemp, Error, TEXT("Invalid ViewIndex: %d, Views.Num(): %d"), ViewIndex, Views.Num());
                    }
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
