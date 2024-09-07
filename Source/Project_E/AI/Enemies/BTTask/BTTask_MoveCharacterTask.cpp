// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/BTTask/BTTask_MoveCharacterTask.h"
#include "NavigationSystem.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "Character/PJECharacterBase.h"

bool UBTTask_MoveCharacterTask::IsLocationInNavMesh(ACharacter* CurrentCharacter, FVector TargetLocation)
{
    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (NavSys)
    {
        FNavLocation NavLocation;

        bool bOnNavMesh = NavSys->ProjectPointToNavigation(TargetLocation, NavLocation, FVector(1.0f, 1.0f, CurrentCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * 4.0f));

        if (bOnNavMesh)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool UBTTask_MoveCharacterTask::IsFrontEmpty(ACharacter* CurrentCharacter, FVector DirVec)
{
    if (!DirVec.Normalize())
    {
        return false;
    }

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(CurrentCharacter);

    UCapsuleComponent* Capsule = CurrentCharacter->GetCapsuleComponent();
    if (Capsule == nullptr)
    {
        return false;
    }

    // 충돌 검사
    FVector Start = CurrentCharacter->GetActorLocation();
    Start.Z -= Capsule->GetScaledCapsuleHalfHeight() * 0.9f;
    FVector End = Start + DirVec * Capsule->GetScaledCapsuleRadius() * 1.1f;
    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
    if (bHit == true)
    {
        if (HitResult.GetActor()->IsA(APJECharacterBase::StaticClass()) == true)
        {
            return true;
        }
    }
    return !bHit;
}

bool UBTTask_MoveCharacterTask::IsCliff(ACharacter* CurrentCharacter, FVector DirVec)
{
    if (!DirVec.Normalize())
    {
        return false;
    }

    UCapsuleComponent* Capsule = CurrentCharacter->GetCapsuleComponent();
    if (Capsule == nullptr)
    {
        return false;
    }

    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(CurrentCharacter);

    FVector Start = CurrentCharacter->GetActorLocation() + DirVec * Capsule->GetScaledCapsuleRadius();
    Start.Z -= Capsule->GetScaledCapsuleHalfHeight() - 25.0f;
    FVector End = Start;
    End.Z -= 50.0f;

    FHitResult HitResult;
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams);
    
    return !bHit;
}
