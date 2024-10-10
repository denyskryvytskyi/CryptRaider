// Copyright Denys Kryvytskyi. All Rights Reserved.
#include "CryptRaiderGameMode.h"
#include "CryptRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/GameUserSettings.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void ACryptRaiderGameMode::BeginPlay()
{
    Super::BeginPlay();

    // change user settings
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    UserSettings->ScalabilityQuality.SetFromSingleQualityLevel(1); // Set to Medium
    UserSettings->ApplySettings(false);
}
