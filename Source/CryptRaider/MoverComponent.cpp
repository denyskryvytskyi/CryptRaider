// Copyright Denys Kryvytskyi. All Rights Reserved.

#include "MoverComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

UMoverComponent::UMoverComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMoverComponent::BeginPlay()
{
    Super::BeginPlay();

    OriginLocation = GetOwner()->GetActorLocation();
}

void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector TargetLocation = OriginLocation;

    const auto Owner = GetOwner();
    const FVector CurrentLocation = Owner->GetActorLocation();

    if (bMovingEnabled) {
        TargetLocation += MoveOffset;
    }

    if (CurrentLocation.Equals(TargetLocation)) {
        bSoundSpawned = false;
        return;
    }

    if (MoveSound && !bSoundSpawned) {
        bSoundSpawned = true;
        UGameplayStatics::PlaySoundAtLocation(this, MoveSound, CurrentLocation);
    }

    const float Speed = MoveOffset.Length() / MoveTime;
    const auto NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);

    Owner->SetActorLocation(NewLocation);
}

void UMoverComponent::EnableMoving(bool enabled)
{
    bMovingEnabled = enabled;
}
