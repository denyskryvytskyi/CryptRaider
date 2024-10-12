// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"

#include "TriggerComponent.generated.h"

class UMoverComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent {
    GENERATED_BODY()

public:
    UTriggerComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void SetMover(UMoverComponent* NewMover);

protected:
    virtual void BeginPlay() override;

private:
    AActor* GetUnlockActor() const;

private:
    UPROPERTY(EditAnywhere)
    FName UnlockActorTag;

    UPROPERTY(EditAnywhere)
    bool bUnlockObjectAttachable { false }; // should the unlock object be attached to the unlocked object

    UPROPERTY(EditAnywhere)
    bool bGrabbedCanUnlock { false };   // can be unlocked with grabbed object (like holding a key for a door)

    UPROPERTY(EditAnywhere)
    bool bTriggerableOnlyOnce { false };    // can be used once

    UPROPERTY(EditAnywhere)
    bool bQuestCompleteTrigger { false };

private:
    UMoverComponent* Mover { nullptr };
    bool bAlreadyTriggered { false };
};
