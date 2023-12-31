// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "TheyMustDie/Character/Player2DCharacter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CharacterBlueprints.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API UCharacterBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Spawns a player character at the given position
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Spawn Player Character", Keywords = "character spawn player"), Category = "Character")
	static APlayer2DCharacter *SpawnPlayerCharacter(UPARAM(DisplayName = "Position")const FVector &Position);
	
};
