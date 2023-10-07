// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GrabberComponent.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabberComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

	// Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void Grab();

    UFUNCTION(BlueprintCallable)
    void Release();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    bool TryHit(FHitResult& hitResult);

private:
    UPROPERTY(EditAnywhere)
    float MaxGrabDistance { 400.0f };
	
	UPROPERTY(EditAnywhere)
    float GrabRadius { 100.0f };

	UPROPERTY(EditAnywhere)
    float HoldDistance { 100.0f };

    UPhysicsHandleComponent* PhysicsHandle { nullptr };
};
