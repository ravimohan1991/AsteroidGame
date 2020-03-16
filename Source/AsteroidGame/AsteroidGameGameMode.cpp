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

	AsteroidsSpawnPoints.Add(FVector(590, -1770, 240));
	AsteroidsSpawnPoints.Add(FVector(-810, -1770, 240));
	AsteroidsSpawnPoints.Add(FVector(-1350, -1010, 240));
	AsteroidsSpawnPoints.Add(FVector(-1350, 1250, 240));
	AsteroidsSpawnPoints.Add(FVector(-810, 1730, 240));
	AsteroidsSpawnPoints.Add(FVector(590, 1730, 240));
	AsteroidsSpawnPoints.Add(FVector(990, 1310, 240));
	AsteroidsSpawnPoints.Add(FVector(990, -1090, 240));
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
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(AsteroidSpawnerHandle, this, &AAsteroidGameGameMode::SpawnAsteroid, AsteroidSpawnLoopTime, true);
	}
}

void AAsteroidGameGameMode::SpawnAsteroid()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the asteroid projectile
		World->SpawnActor<AAsteroidGameAsteroid>(Asteroids.GetData()[FMath::RandRange(int32(0), int32(Asteroids.Num() - 1))], AsteroidsSpawnPoints.GetData()[FMath::RandRange(int32(0), int32(AsteroidsSpawnPoints.Num() - 1))], FRotator(0, 0, 0), ActorSpawnParams);
	}
}

void AAsteroidGameGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(AsteroidSpawnerHandle);
	}
}