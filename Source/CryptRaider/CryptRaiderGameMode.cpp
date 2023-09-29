// Copyright Epic Games, Inc. All Rights Reserved.

#include "CryptRaiderGameMode.h"
#include "CryptRaiderCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACryptRaiderGameMode::ACryptRaiderGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
