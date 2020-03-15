#include "AsteroidGameGameMode.h"
#include "AsteroidGamePlayerController.h"
#include "AsteroidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "AsteroidGameAsteroid.h"

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
}

void AAsteroidGameGameMode::EndGame()
{
	DisplayGameOver();
}

void AAsteroidGameGameMode::DisplayGameOver_Implementation()
{
}

void AAsteroidGameGameMode::BeginPlay()
{
	/*UWorld* const World = GetWorld();
	if (World != NULL)
	{
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the asteroid projectile
		World->SpawnActor<AAsteroidGameAsteroid>(AsteroidClass, FVector(-350, -540, 270), FRotator(0, 0, 0), ActorSpawnParams);
	}*/
}