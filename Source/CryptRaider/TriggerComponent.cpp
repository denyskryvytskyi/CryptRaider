// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"
#include "MoverComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    const bool Enabled = !IsTriggerableOnlyOnce || (IsTriggerableOnlyOnce && !IsAlreadyTriggered);

    if (Enabled && Mover)
    {
        const auto UnlockActor = GetUnlockActor();
        if (UnlockActor)
        {
            if (IsUnlockObjectAttachable)
            {
                if (auto UnlockActorRootComponent = Cast<UPrimitiveComponent>(UnlockActor->GetRootComponent()))
                {
                    UnlockActorRootComponent->SetSimulatePhysics(false);
                }
                UnlockActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
            }


            Mover->EnableMoving(true);
            IsAlreadyTriggered = true;
        }
        else {
            Mover->EnableMoving(false);
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
        for (const auto tag : Actor->Tags) {
            UE_LOG(LogTemp, Display, TEXT("Overlaping with tag: %s"), *tag.ToString());
        }
        
        const bool IsGrabbed = Actor->ActorHasTag("Grabbed");
        if (Actor->ActorHasTag(UnlockActorTag) && (IsGrabbedCanUnlock || !IsGrabbed)) {

            UE_LOG(LogTemp, Display, TEXT("====== Wall unlocked ======="));
            return Actor;
        }
    }

    return nullptr;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}
