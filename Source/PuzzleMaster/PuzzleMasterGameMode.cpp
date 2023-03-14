// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleMasterGameMode.h"
#include "PuzzleMasterCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleMasterGameMode::APuzzleMasterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
