// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "Engine/World.h"

#include "DrawDebugHelpers.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

    if (!PhysicsHandle)
    {
        UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent!"));
    }
}

bool UGrabberComponent::TryHit(FHitResult& hitResult)
{
    const auto* World = GetWorld();

    const auto Start = GetComponentLocation();
    const auto End = Start + (GetForwardVector() * MaxGrabDistance);
    DrawDebugLine(World, Start, End, FColor::Red);
    DrawDebugSphere(World, End, 10.0f, 10, FColor::Blue, false, 5.0f);

    // Geometry sweeping
    const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(GrabRadius);

    if (World->SweepSingleByChannel(hitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape)) {
        // debug
        DrawDebugSphere(World, hitResult.Location, 10.0f, 10, FColor::Red, false, 5.0f);
        DrawDebugSphere(World, hitResult.ImpactPoint, 10.0f, 10, FColor::Green, false, 5.0f);
        UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *hitResult.GetActor()->GetActorNameOrLabel());

        return true;
    }

    return false;
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent())
    {
        const FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
        PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
    }
}

void UGrabberComponent::Grab()
{
    if (!PhysicsHandle)
    {
        return;
    }

    FHitResult HitResult;
    if (TryHit(HitResult)) {
        auto GrabbedActor =HitResult.GetActor();
        GrabbedActor->Tags.Add("Grabbed");

        PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.ImpactPoint, GetComponentRotation());
    }
}

void UGrabberComponent::Release()
{
    if (PhysicsHandle)
    {
        auto GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
        if (GrabbedComponent)
        {
            auto Owner = GrabbedComponent->GetOwner();
            Owner->Tags.Remove("Grabbed");

            PhysicsHandle->ReleaseComponent();

            UE_LOG(LogTemp, Display, TEXT("Grabbed component released"));
        }
    }
}

