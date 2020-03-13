#include "AsteroidGameGameMode.h"
#include "AsteroidGamePlayerController.h"
#include "AsteroidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

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
	Destroy();
}
