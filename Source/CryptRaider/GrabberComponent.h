// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"

#include "GrabberComponent.generated.h"

class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabberComponent : public USceneComponent {
    GENERATED_BODY()

public:
    UGrabberComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Grab();

    UFUNCTION(BlueprintCallable)
    void Release();

protected:
    virtual void BeginPlay() override;

private:
    bool TryHit(FHitResult& hitResult);

private:
    UPROPERTY(EditAnywhere)
    float MaxGrabDistance { 400.0f };

    UPROPERTY(EditAnywhere)
    float GrabRadius { 100.0f };

    UPROPERTY(EditAnywhere)
    float HoldDistance { 100.0f };

    UPROPERTY(EditAnywhere)
    USoundBase* PickupSound { nullptr };

    UPROPERTY(EditAnywhere)
    USoundBase* DropSound { nullptr };

    UPhysicsHandleComponent* PhysicsHandle { nullptr };
};
