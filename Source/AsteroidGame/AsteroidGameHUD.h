#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AsteroidGameHUD.generated.h"

UCLASS()
class ASTEROIDGAME_API AAsteroidGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
	
	/**
	* The font of the text diaplayed on the HUD
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUD)
	UFont* TextFont;
};
