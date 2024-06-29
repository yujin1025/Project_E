// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTComposite_RandomSelector.h"

#include "BTComposite_RandomSelector.h"

UBTComposite_RandomSelector::UBTComposite_RandomSelector()
{
    NodeName = "Random Selector";
}

int32 UBTComposite_RandomSelector::GetNextChildHandler(FBehaviorTreeSearchData& SearchData, int32 PrevChild, EBTNodeResult::Type LastResult) const
{
    if (PrevChild == BTSpecialChild::NotInitialized)
    {
        // 자식 인덱스 배열 생성
        TArray<int32> ChildIndices;
        for (int32 i = 0; i < Children.Num(); i++)
        {
            ChildIndices.Add(i);
        }

        // 배열을 무작위로 섞기
        int32 NextChildIndex = FMath::RandRange(0, Children.Num() - 1);

        return NextChildIndex;
    }

    return BTSpecialChild::ReturnToParent;
}
