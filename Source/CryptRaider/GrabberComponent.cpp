// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "Engine/World.h"

#include "DrawDebugHelpers.h"

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

	// ...
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto* World = GetWorld();

	const auto Start = GetComponentLocation();
    const auto End = Start + (GetForwardVector() * MaxGrabDistance);
    DrawDebugLine(World, Start, End, FColor::Red);

	// Geometry sweeping
    FHitResult HitResult;
    const FCollisionShape CollisionShape = FCollisionShape::MakeSphere(GrabRadius);

	if (World->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, CollisionShape))
	{
        UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitResult.GetActor()->GetActorNameOrLabel());
	}
}

