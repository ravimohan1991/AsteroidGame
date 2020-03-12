// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AsteroidGameGameMode.h"
#include "AsteroidGamePlayerController.h"
#include "AsteroidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAsteroidGameGameMode::AAsteroidGameGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AAsteroidGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerLives = 3;
}

void AAsteroidGameGameMode::PlayerDied(AController* NewPlayer)
{
	PlayerLives--;
	// May want to incorporate bullet projectile destroy logic here.
	if (PlayerLives > 0) {
		//RestartPlayer(NewPlayer);
	}
}