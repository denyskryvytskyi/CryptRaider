// Copyright Denys Kryvytskyi. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "CryptRaiderGameMode.generated.h"

UCLASS(minimalapi)
class ACryptRaiderGameMode : public AGameModeBase {
    GENERATED_BODY()

public:
    ACryptRaiderGameMode();

    void BeginPlay() override;
};
