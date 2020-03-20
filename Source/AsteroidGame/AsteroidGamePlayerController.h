#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AsteroidGamePlayerController.generated.h"

UCLASS()
class AAsteroidGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/**
	* The constructor for setting default properties of class. 
	*/
	AAsteroidGamePlayerController();

	/**
	* Sets the LivesLeft and player's viewport.
	* Called by AAsteroidGameCharacter::Die
	*/
	void NotifyDead();

	/**
	* Returns the score of the player.
`	*
	* @see AAsteroidGameHUD::DrawHUD
	*/
	float GetScore() { return Score; }
	
	/**
	* Returns remaining lives of the player.
`	*
	* @see AAsteroidGameHUD::DrawHUD
	*/
	int32 GetLivesLeft() { return LivesLeft; }
	
	/**
	* Increases the score of the player when he/she successfully hits
	* the asteroid.
	*
	* @see  AAsteroidGameAsteroid::TakeDamage
	*/
	void IncrementScore( float Value ) { Score += Value; }

	/**
	* Respawn the character after specified time interval.  Instant respawning
	* doesn't always work.
	*/
	UFUNCTION()
	void ReSpawn();

private:
	/** Lives left */
	int32 LivesLeft;
	
	/** Player score */
	float Score;

	/** Handle for respawn timer */
	FTimerHandle ReSpawnTimerHandle;

protected:
	/** Function called at the end of the game. Clears the timer. */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};


