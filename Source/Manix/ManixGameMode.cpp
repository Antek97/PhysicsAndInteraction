// Copyright Epic Games, Inc. All Rights Reserved.

#include "ManixGameMode.h"
#include "ManixHUD.h"
#include "ManixCharacter.h"
#include "UObject/ConstructorHelpers.h"

AManixGameMode::AManixGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AManixHUD::StaticClass();
}
