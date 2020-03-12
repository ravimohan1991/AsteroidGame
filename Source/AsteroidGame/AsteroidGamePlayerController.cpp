// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "AsteroidGamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "AsteroidGameCharacter.h"
#include "Engine/World.h"

AAsteroidGamePlayerController::AAsteroidGamePlayerController()
{
	bShowMouseCursor = true;
}

void AAsteroidGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AAsteroidGamePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
}

