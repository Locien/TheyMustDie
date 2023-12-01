// ©Kris and Tashhhh 2023


#include "UtilityBlueprints.h"
#include "../Debug.h"

FVector2D UUtilityBlueprints::GetRotationVectorFromCenter(UPARAM(DisplayName = "Screen Position")const FVector2D& Position, UPARAM(DisplayName = "Viewport Size")const FIntVector& ViewportSize)
{
	FVector2D ViewportFloat = FVector2D((double)ViewportSize.X, (double)ViewportSize.Y);
	return FVector2D();
}