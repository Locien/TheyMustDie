// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ControllerBlueprints.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API UControllerBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Possesses a character according to a given character number. Returns true if successful, otherwise false.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Possess Player Character", Keywords = "possess player character"), Category = "Character")
	static bool PossessPlayerCharacter(UPARAM(DisplayName = "Character Number")const int& Number);
	
};
