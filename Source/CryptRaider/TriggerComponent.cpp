// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "TriggerComponent.h"
#include "MoverComponent.h"
#include "CryptRaider/CryptRaiderGameMode.h"
#include "Kismet/GameplayStatics.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const bool Enabled = !bTriggerableOnlyOnce || (bTriggerableOnlyOnce && !bAlreadyTriggered);

    if (Enabled) {
        const auto UnlockActor = GetUnlockActor();
        if (UnlockActor) {
            if (bUnlockObjectAttachable) {
                if (auto UnlockActorRootComponent = Cast<UPrimitiveComponent>(UnlockActor->GetRootComponent())) {
                    UnlockActorRootComponent->SetSimulatePhysics(false);
                }
                UnlockActor->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            }

            bAlreadyTriggered = true;

            if (bQuestCompleteTrigger) {
                if (ACryptRaiderGameMode* GameMode = Cast<ACryptRaiderGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
                    GameMode->ShowQuestCompleteWidget();
                }
            }

            if (Mover) {
                Mover->EnableMoving(true);
            }
        } else {
            if (Mover) {
                Mover->EnableMoving(false);
            }
        }
    }
}

void UTriggerComponent::SetMover(UMoverComponent* NewMover)
{
    Mover = NewMover;
}

AActor* UTriggerComponent::GetUnlockActor() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for (const auto Actor : Actors) {
        const bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (Actor->ActorHasTag(UnlockActorTag) && (bGrabbedCanUnlock || !IsGrabbed)) {
            return Actor;
        }
    }

    return nullptr;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}
