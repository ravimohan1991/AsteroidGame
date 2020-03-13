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

private:
	int32 LivesLeft;
};


