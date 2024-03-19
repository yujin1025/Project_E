// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/PJESlideButton.h"

void APJESlideButton::ButtonBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	Super::ButtonBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, Hit);

	// a. Show Interaction UI
	// b. Enable Interaction
}

void APJESlideButton::ButtonEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::ButtonEndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	// a. Show Interaction UI
	// b. Enable Interaction
}

// TODO: Make Interact
// Interaction Key is [E] (can be changed)
// Interaction Type is [Hold]
// if Interact..
// a. 캐릭터를 애니메이션에 적절한 위치로 이동시킨다 (이동안은 상호작용 불가)
// b. Push 애니메이션 실행, 버튼 interact 실행 (여기서부터 상호작용 가능?)
// c. 캐릭터도 같이 움직임
// d. 
