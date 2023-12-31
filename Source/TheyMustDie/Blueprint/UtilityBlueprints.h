// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityBlueprints.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API UUtilityBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Returns the rotation vector point from the center of the screen to a point specified in viewport coordinates. Useful to get a character to face the way the mouse cursor is pointing.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Rotation Vector from Center", Keywords = "get rotation vector from center"), Category = "TheyMustDie")
	static FVector2D GetRotationVectorFromCenter(UPARAM(DisplayName = "Screen Position")const FVector2D &Position, UPARAM(DisplayName = "Viewport Size")const FIntVector &ViewportSize);
	
};
