#include "AsteroidGameHUD.h"
#include "Engine/Canvas.h"
#include "Engine.h"
#include "AsteroidGamePlayerController.h"

void AAsteroidGameHUD::DrawHUD()
{
	Super::DrawHUD();
	
	float XL, YL;

	if (Canvas == nullptr || GEngine == nullptr)
		return;

	Canvas->SetDrawColor(255, 255, 255);

	AAsteroidGamePlayerController* MyController = Cast<AAsteroidGamePlayerController>(GetOwningPlayerController());
	if (MyController && TextFont)
	{
		Canvas->StrLen(TextFont, FString("PlayerLife:"), XL, YL);
		Canvas->DrawText(TextFont, FString::Printf(TEXT("Lives: %d"), MyController->GetLivesLeft()), 2 * XL, Canvas->ClipY - 1.5 * YL);
		Canvas->DrawText(TextFont, FString::Printf(TEXT("Score: %f"), MyController->GetScore()), 4 * XL, Canvas->ClipY - 1.5 * YL);
	}
}