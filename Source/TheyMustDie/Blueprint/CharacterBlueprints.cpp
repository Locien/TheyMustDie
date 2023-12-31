// ©Kris and Tashhhh 2023

#include "CharacterBlueprints.h"
#include "Engine/Engine.h"

APlayer2DCharacter* UCharacterBlueprints::SpawnPlayerCharacter(UPARAM(DisplayName = "Position")const FVector& Position)
{
	FWorldContext Context = GEngine->GetWorldContexts().Last();
	UWorld* World = Context.World();

	FVector ZAdjustedPos = FVector(Position.X, Position.Y, 15.F); //Spawn at 15 units above the ground for now
	APlayer2DCharacter *SpawnedCharacter = World->SpawnActor<APlayer2DCharacter>(APlayer2DCharacter::StaticClass(), ZAdjustedPos, FRotator(0.F, 0.F, 0.F));
	return SpawnedCharacter;
}

