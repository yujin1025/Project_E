// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Enemies/PJEShadowArea.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "AI/Enemies/PJEShadowGenerator.h"
#include "Character/PJECharacterShadowA.h"
#include "Character/PJECharacterPlayer.h"
#include "AI/Managers/PJEShadowGeneratorManager.h"

APJEShadowArea::APJEShadowArea()
{
    PrimaryActorTick.bCanEverTick = true;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APJEShadowArea::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &APJEShadowArea::OnOverlapEnd);

    BackgroundAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BackgroundAudioComponent"));
    BackgroundAudioComponent->SetupAttachment(RootComponent);

    BackgroundSoundCue = nullptr;

    bIsPlayerInArea = false;

    MaxGenetatorNum = 3;
    MaxShadowANum = 6;
}

void APJEShadowArea::BeginPlay()
{
    Super::BeginPlay();
}

void APJEShadowArea::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APJEShadowArea::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(APJECharacterPlayer::StaticClass()))
    {
        bIsPlayerInArea = true;

        // 플레이어가 트리거 박스에 들어왔을 때 배경음악 재생
        if (!BackgroundAudioComponent->IsPlaying() && BackgroundSoundCue)
        {
            BackgroundAudioComponent->Play();
            SetBackgroundVolume(UPJEShadowGeneratorManager::GetInstance()->GetShadowGeneratorsCount() / MaxGenetatorNum);
        }

        PlayShadowASound();
    }
}

void APJEShadowArea::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->IsA(APJECharacterPlayer::StaticClass()))
    {
        bIsPlayerInArea = false;
        // 플레이어가 트리거 박스를 나갔을 때 배경음악 정지
        if (BackgroundAudioComponent->IsPlaying())
        {
            BackgroundAudioComponent->Stop();
        }

        for (APJECharacterShadowA* ShadowA : ShadowAArr)
        {
            ShadowA->StopSound();
        }
    }
}

void APJEShadowArea::SetBackgroundVolume(float Volume)
{
    if (BackgroundAudioComponent)
    {
        BackgroundAudioComponent->SetVolumeMultiplier(FMath::Clamp(Volume, 0.0f, 1.0f));
    }
}

void APJEShadowArea::PlayShadowASound()
{
    for (APJECharacterShadowA* ShadowA : ShadowAArr)
    {
        ShadowA->PlaySound();
        ShadowA->SetLaughVolume(ShadowAArr.Num() / MaxShadowANum);
    }
}

bool APJEShadowArea::GetIsPlayerInArea()
{
    return bIsPlayerInArea;
}
