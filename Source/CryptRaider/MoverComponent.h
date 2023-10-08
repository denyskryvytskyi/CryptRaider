// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void EnableMoving(bool enabled);

private:
    UPROPERTY(EditAnywhere)
    FVector MoveOffset;

	UPROPERTY(EditAnywhere)
    float MoveTime { 3.0f };

    UPROPERTY(EditAnywhere)
    bool MovingEnabled { false };
	
	UPROPERTY(EditAnywhere)
    bool ResetToOriginEnabled { false };


private:
    FVector OriginLocation;
};
