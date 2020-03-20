#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameAsteroid.h"
#include "AsteroidGameGameMode.generated.h"

UCLASS(minimalapi)
class AAsteroidGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsteroidGameGameMode();

	/**
	* Called when the game ends.
	* 
	* @see AAsteroidGamePlayerController::NotifyDead
	*/
	void EndGame();

	/**
	* Displays game over widget. Overriden in the blueprint
	* 
	* @see Blueprint'/Game/TopDownCPP/Blueprints/BP_AsteroidGameGameMode.BP_AsteroidGameGameMode'
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Misc")
	void DisplayGameOver();

	/**
	* Spawns asteroids of random size at random points in the level at
	* fixed interval (configurable) of time.
	*/
	UFUNCTION()
	void SpawnAsteroid();

protected:
	/**
	* Called at the start of the game. Sets a timer for spawning asteroids.
	*/
	virtual void BeginPlay() override;

	/**
	* Called at the end of the game. Clears the timer.
	*/
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/**
	* Handle for SpawnAsteroid timer.
	*/
	FTimerHandle AsteroidSpawnerHandle;

	/**
	* Configurable asteroid type of various sizes.
	*/
	UPROPERTY(EditAnywhere, Category = "GameDynamics")
	TArray<TSubclassOf<class AAsteroidGameAsteroid>> Asteroids;

	/**
	* The timer loop time interval.
	*/
	UPROPERTY(EditAnywhere, Category = "GameDynamics")
	float AsteroidSpawnLoopTime;

	/**
	* Locations in the level (outside the screen) to spawn asteroids.
	*/
	TArray<FVector> AsteroidsSpawnPoints;
};



