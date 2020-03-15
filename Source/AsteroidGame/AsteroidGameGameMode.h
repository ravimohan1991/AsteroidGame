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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Misc")
	void DisplayGameOver();

	UPROPERTY(EditAnywhere, Category = "Misc")
	TSubclassOf<class AAsteroidGameAsteroid> AsteroidClass;
protected:

	virtual void BeginPlay() override;
};



