#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "PJEShadowArea.generated.h"

UCLASS()
class PROJECT_E_API APJEShadowArea : public AActor
{
    GENERATED_BODY()

    public:
    APJEShadowArea();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
    bool bIsPlayerInArea;

    float MaxGenetatorNum;
    float MaxShadowANum;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> BackgroundSoundCue;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<class UBoxComponent> TriggerBox;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<class UAudioComponent> BackgroundAudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shadow")
    TArray<TObjectPtr<class APJEShadowGenerator>> ShadowGeneratorArr;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Shadow")
    TArray<TObjectPtr<class APJECharacterShadowA>> ShadowAArr;

    UFUNCTION()
    void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
        class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    void SetBackgroundVolume(float Volume);

    void PlayShadowASound();

    bool GetIsPlayerInArea();
};
