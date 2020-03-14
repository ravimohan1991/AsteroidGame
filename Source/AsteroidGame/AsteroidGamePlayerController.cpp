#include "AsteroidGamePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "AsteroidGameCharacter.h"
#include "Engine/World.h"
#include "AsteroidGameGameMode.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"

AAsteroidGamePlayerController::AAsteroidGamePlayerController()
{
	bShowMouseCursor = true;
	LivesLeft = 3;
}

void AAsteroidGamePlayerController::NotifyDead()
{
	AAsteroidGameGameMode* GameMode = GetWorld()->GetAuthGameMode<AAsteroidGameGameMode>();

	if (GameMode == nullptr)
	{
		return;
	}

	if (LivesLeft > 1)
	{
		//GameMode->RestartPlayer(this);
		GetWorld()->GetTimerManager().SetTimer(ReSpawnTimerHandle, this, &AAsteroidGamePlayerController::ReSpawn, 1.0f, false);
		LivesLeft--;
	}
	else
	{
		GameMode->EndGame();
	}
	
	// Set the view as per camera
	for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetViewTargetWithBlend(*ActorItr);
		break;
	}
}

void AAsteroidGamePlayerController::ReSpawn()
{
	AAsteroidGameGameMode* GameMode = GetWorld()->GetAuthGameMode<AAsteroidGameGameMode>();

	if(GameMode)
		GameMode->RestartPlayer(this);

	// Set the view as per camera
	for (TActorIterator<ACameraActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SetViewTargetWithBlend(*ActorItr);
		break;
	}
}

void AAsteroidGamePlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(ReSpawnTimerHandle);
}