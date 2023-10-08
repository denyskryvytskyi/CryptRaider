// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

#include "TriggerComponent.generated.h"

class UMoverComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
    UTriggerComponent();

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void SetMover(UMoverComponent* NewMover);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    AActor* GetUnlockActor() const;

private:
    UPROPERTY(EditAnywhere)
    FName UnlockActorTag;

    UPROPERTY(EditAnywhere)
    bool IsUnlockObjectAttachable { false };

    UPROPERTY(EditAnywhere)
    bool IsGrabbedCanUnlock { false };

    UPROPERTY(EditAnywhere)
    bool IsTriggerableOnlyOnce { false };

private:
    UMoverComponent* Mover { nullptr };
    bool IsAlreadyTriggered { false };
};
