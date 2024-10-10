// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "GrabberComponent.h"

#include "Engine/World.h"

#include "DrawDebugHelpers.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Kismet/GameplayStatics.h"

UGrabberComponent::UGrabberComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UGrabberComponent::BeginPlay()
{
    Super::BeginPlay();

    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent!"));
    }
}

bool UGrabberComponent::TryHit(FHitResult& hitResult)
{
    const auto* World = GetWorld();

    const auto Start = GetComponentLocation();
    const auto End = Start + (GetForwardVector() * MaxGrabDistance);

    // Geometry sweeping
    const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(GrabRadius);

    if (World->SweepSingleByChannel(hitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape)) {
        /* DrawDebugSphere(World, hitResult.Location, 10.0f, 10, FColor::Red, false, 5.0f);
         DrawDebugSphere(World, hitResult.ImpactPoint, 10.0f, 10, FColor::Green, false, 5.0f);*/
        UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *hitResult.GetActor()->GetActorNameOrLabel());

        return true;
    }

    return false;
}

void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent()) {
        const FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
        PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
    }
}

void UGrabberComponent::Grab()
{
    if (!PhysicsHandle) {
        return;
    }

    FHitResult HitResult;
    if (TryHit(HitResult)) {
        auto* GrabbedComponent = HitResult.GetComponent();
        GrabbedComponent->SetSimulatePhysics(true);

        auto* GrabbedActor = HitResult.GetActor();
        GrabbedActor->Tags.Add("Grabbed");
        GrabbedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

        PhysicsHandle->GrabComponentAtLocationWithRotation(GrabbedComponent, NAME_None, HitResult.ImpactPoint, GetComponentRotation());

        if (PickupSound) {
            UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GrabbedActor->GetActorLocation());
        }
    }
}

void UGrabberComponent::Release()
{
    if (PhysicsHandle) {
        auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
        if (GrabbedComponent) {
            auto Owner = GrabbedComponent->GetOwner();
            Owner->Tags.Remove("Grabbed");

            PhysicsHandle->ReleaseComponent();

            UE_LOG(LogTemp, Display, TEXT("Grabbed component released"));

            if (DropSound) {
                UGameplayStatics::PlaySoundAtLocation(this, DropSound, Owner->GetActorLocation());
            }
        }
    }
}
