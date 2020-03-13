#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AsteroidGameGameMode.generated.h"

UCLASS(minimalapi)
class AAsteroidGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAsteroidGameGameMode();

	void EndGame();

};



