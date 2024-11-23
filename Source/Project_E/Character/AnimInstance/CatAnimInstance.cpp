// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AnimInstance/CatAnimInstance.h"

#include "Character/PJECharacterCat.h"
#include "Character/PJECharacterPlayer.h"

void UCatAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CatCharacter = Cast<APJECharacterPlayer>(TryGetPawnOwner());
}

void UCatAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if(!CatCharacter)
	{
		CatCharacter = Cast<APJECharacterPlayer>(TryGetPawnOwner());
	}

	if (CatCharacter)
	{
		FVector Start = CatCharacter->GetActorLocation() + FVector(0, 0, -88);
		FVector End = Start - FVector(0, 0, 500);

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(CatCharacter);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

		if (bHit)
		{
			DistanceToGround = (HitResult.Location - Start).Size();
		}
		else
		{
			DistanceToGround = 500.0f; 
		}
	}
}

void UCatAnimInstance::AnimNotify_L_DashTrail()
{
	if(CatCharacter)
	{
		APJECharacterCat* Cat = Cast<APJECharacterCat>(CatCharacter);
		FVector FootLocation = Cat->GetMesh()->GetSocketLocation(FName("L_Foot"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, FootLocation);
	}
}

void UCatAnimInstance::AnimNotify_Land()
{
	if(CatCharacter)
	{
		APJECharacterCat* Cat = Cast<APJECharacterCat>(CatCharacter);
		FVector FootLocation = Cat->GetMesh()->GetSocketLocation(FName("Bottom"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LandEffect, FootLocation);
	}
}

void UCatAnimInstance::AnimNotify_R_DashTrail()
{
	if(CatCharacter)
	{
		APJECharacterCat* Cat = Cast<APJECharacterCat>(CatCharacter);
		FVector FootLocation = Cat->GetMesh()->GetSocketLocation(FName("R_Foot"));
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DashEffect, FootLocation);
	}
}
