// Copyright Epic Games, Inc. All Rights Reserved.

#include "Practico1GameMode.h"
#include "Practico1Character.h"
#include "UObject/ConstructorHelpers.h"

APractico1GameMode::APractico1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
