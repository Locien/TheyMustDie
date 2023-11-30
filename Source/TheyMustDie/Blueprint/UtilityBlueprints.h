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
	//Returns the rotation from the center of the screen to a point specified in viewport coordinates. Useful to get projectiles to face a certain direction accord to a mouse click for example.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Rotation to Point from Center", Keywords = "get rotation to point from center"), Category = "TheyMustDie")
	static FRotator GetRotationFromCenter(UPARAM(DisplayName = "Screen Position")const FVector2D &Position, UPARAM(DisplayName = "Viewport Size")const FIntVector &ViewportSize);
	
};
