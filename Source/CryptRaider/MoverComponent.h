// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "MoverComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UMoverComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UMoverComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void EnableMoving(bool enabled);

private:
    UPROPERTY(EditAnywhere)
    FVector MoveOffset;

    UPROPERTY(EditAnywhere)
    USoundBase* MoveSound { nullptr };

    UPROPERTY(EditAnywhere)
    float MoveTime { 3.0f };

    UPROPERTY(EditAnywhere)
    bool bMovingEnabled { false };

    bool bSoundSpawned { false };

private:
    FVector OriginLocation;
};
