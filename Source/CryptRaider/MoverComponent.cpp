// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginLocation = GetOwner()->GetActorLocation();
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector TargetLocation = OriginLocation;

	if (MovingEnabled)
	{
        TargetLocation += MoveOffset;
	}

    const auto Owner = GetOwner();
    const FVector CurrentLocation = Owner->GetActorLocation();

	const float Speed = MoveOffset.Length() / MoveTime;
	const auto NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

	Owner->SetActorLocation(NewLocation);
}

void UMoverComponent::EnableMoving(bool enabled)
{
	MovingEnabled = enabled;
}
