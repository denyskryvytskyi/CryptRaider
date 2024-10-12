// Copyright Denys Kryvytskyi. All Rights Reserved.
#include "CryptRaiderGameMode.h"
#include "Blueprint\UserWidget.h"
#include "CryptRaiderCharacter.h"
#include "GameFramework/GameUserSettings.h"
#include "UObject/ConstructorHelpers.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
    : Super()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
    DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ACryptRaiderGameMode::ShowQuestCompleteWidget()
{
    if (UUserWidget* QuestCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), QuestCompleteWidgetClass)) {
        QuestCompleteWidget->AddToViewport();
    }
}

void ACryptRaiderGameMode::BeginPlay()
{
    Super::BeginPlay();

    // change user settings
    UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
    UserSettings->ScalabilityQuality.ViewDistanceQuality = 0;
    UserSettings->ScalabilityQuality.AntiAliasingQuality = 2;
    UserSettings->ScalabilityQuality.PostProcessQuality = 2;
    UserSettings->ScalabilityQuality.ShadowQuality = 2;
    UserSettings->ScalabilityQuality.GlobalIlluminationQuality = 2;
    UserSettings->ScalabilityQuality.ReflectionQuality = 2;
    UserSettings->ScalabilityQuality.TextureQuality = 2;
    UserSettings->ScalabilityQuality.EffectsQuality = 2;
    UserSettings->ScalabilityQuality.FoliageQuality = 0;
    UserSettings->ScalabilityQuality.ShadingQuality = 0;
    UserSettings->ScalabilityQuality.LandscapeQuality = 0;
    UserSettings->ApplySettings(false);
}
