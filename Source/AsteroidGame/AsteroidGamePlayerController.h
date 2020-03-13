#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AsteroidGamePlayerController.generated.h"

UCLASS()
class AAsteroidGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAsteroidGamePlayerController();
	void NotifyDead();
	float GetScore() { return Score; }
	int32 GetLivesLeft() { return LivesLeft; }
	void IncrementScore( float Value ) { Score += Value; }

private:
	int32 LivesLeft;

	float Score;
};


