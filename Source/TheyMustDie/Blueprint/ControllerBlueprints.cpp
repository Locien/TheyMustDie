// ©Kris and Tashhhh 2023


#include "ControllerBlueprints.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "../Character/Player2DCharacter.h"
#include "../Character/Player2DController.h"
#include "../Defines.h"

bool UControllerBlueprints::PossessPlayerCharacter(UPARAM(DisplayName = "Character Number")const int& Number)
{
	if (Number < 0)
	{
		//Add log here
		return false;
	}
	if(Number >= NUMMAXPLAYERCHARACTERS)
	{
		//Add log here
		return false;
	}
	else
	{
		FWorldContext Context = GEngine->GetWorldContexts().Last();
		UWorld *World = Context.World();

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(World, APlayer2DCharacter::StaticClass(), Actors);

		for(int i = 0; i < Actors.Num(); ++i)
		{
			if(Actors[i] != nullptr)
			{
				APlayer2DCharacter *PlayerCharacter = Cast<APlayer2DCharacter>(Actors[i]);
				if(PlayerCharacter != nullptr)
				{
					if(PlayerCharacter->GetPlayerCharacterID() == Number)
					{
						APlayerController *Controller = GEngine->GetFirstLocalPlayerController(World);
						if (Controller != nullptr)
						{
							APlayer2DController *PlayerController = Cast<APlayer2DController>(Controller);
							PlayerController->PossessPlayerCharacter(PlayerCharacter);
							return true; //Found the correct actor and possessed it.
						}
						else
						{
							//Add log here
							return false;
						}
					}
				}
				else
				{
					//Add log here
				}
			}
			else
			{
				//Add log here
			}
		}
		//Add log here
		return false;
	}
}