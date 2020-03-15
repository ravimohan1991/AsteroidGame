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

	void EndGame();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Misc")
	void DisplayGameOver();

	UFUNCTION()
	void SpawnAsteroid();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	FTimerHandle AsteroidSpawnerHandle;

	UPROPERTY(EditAnywhere, Category = "GameDynamics")
	TArray<TSubclassOf<class AAsteroidGameAsteroid>> Asteroids;

	UPROPERTY(EditAnywhere, Category = "GameDynamics")
	float AsteroidSpawnLoopTime;

	TArray<FVector> AsteroidsSpawnPoints;
};



