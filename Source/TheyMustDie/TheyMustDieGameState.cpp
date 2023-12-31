// ©Kris and Tashhhh 2023

#include "TheyMustDieGameState.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Paper2DCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Debug.h"

ATheyMustDieGameState *ATheyMustDieGameState::Self = nullptr;

ATheyMustDieGameState::ATheyMustDieGameState()
{
	Self = this;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = true;
	GameRunning = false;
	GameOverType = NOT_GAME_OVER;

	ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("WidgetBlueprint'/Game/UI/GameOver/GameOverWidget.GameOverWidget_C'"));
	if(WidgetClassFinder.Succeeded())
	{
		GameOverWidget = WidgetClassFinder.Class;
	}
	else
		Debug::ErrorMessage("Unable to load game over widget in %s", __FUNCTION__);
}

void ATheyMustDieGameState::StartGame()
{
	if(Self)
	{
		if(!Self->GameRunning)
		{
			Self->GameOverType = NOT_GAME_OVER;
			Self->PrimaryActorTick.SetTickFunctionEnable(true);
			Self->GameRunning = true;
			Self->GetPlayerReferences();
			Self->GetRelicReference();
		}
		else
			Debug::ErrorMessage("Attempt to start game when it's already running");
	}
	else
		Debug::ErrorMessage("ATheyMustDieGameState::Self returned nullptr in %s", __FUNCTION__);
}

void ATheyMustDieGameState::EndGame()
{
	if(Self)
	{
		if(Self->GameRunning)
		{
			Self->PrimaryActorTick.SetTickFunctionEnable(false);
			Self->GameRunning = false;
			Self->ResetPlayerReferences();
			Self->ResetRelicReference();
			Self->StopAllCharacterLogic();
		}
		else
			Debug::ErrorMessage("Attempt to end game when it's not running");
	}
	else
		Debug::ErrorMessage("ATheyMustDieGameState::Self returned nullptr in %s", __FUNCTION__);
}

bool ATheyMustDieGameState::isGameRunning()
{
	if(Self)
		return Self->GameRunning;
	else
	{
		Debug::ErrorMessage("ATheyMustDieGameState::Self returned nullptr in %s", __FUNCTION__);
		return false;
	}
}

FText ATheyMustDieGameState::GetGameOverText()
{
	if(Self)
	{
		switch(Self->GameOverType)
		{
			case GAME_OVER_PLAYER_DEAD:
			{
				return FText::FromString("THOU ART DEAD AND THY WORLD IS DOOMED");
			}
			case GAME_OVER_RELIC_DESTROYED:
			{
				return FText::FromString("THINE RELIC IS LOST AND SO IS ALL HOPE");
			}
			default:
			{
				return FText::FromString("ERROR");
			}
		}
	}
	else
		return FText::FromString("NULL");
}

void ATheyMustDieGameState::Tick(float Deltatime)
{
	if(GameRunning)
	{
		ProcessLoseCondition();
	}
}

void ATheyMustDieGameState::OnGameOver()
{
	UUserWidget *GameOverScreen = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), GameOverWidget);
	GameOverScreen->AddToViewport();
	EndGame();
}

void ATheyMustDieGameState::ProcessLoseCondition()
{
	if(Player1.IsValid())
	{
		if(!Player1.Get()->isAlive())
		{
			GameOverType = GAME_OVER_PLAYER_DEAD;
			OnGameOver();
			return;
		}
	}
	else
		Debug::ErrorMessage("Player 1 reference is invalid in %s", __FUNCTION__);

	if(SacredRelic.IsValid())
	{
		if(SacredRelic.Get()->isDestroyed())
		{
			GameOverType = GAME_OVER_RELIC_DESTROYED;
			OnGameOver();
			return;
		}
	}
	else
		Debug::ErrorMessage("Sacred relic reference is invalid in %s", __FUNCTION__);
}

void ATheyMustDieGameState::GetPlayerReferences()
{
	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayer2DCharacter::StaticClass(), FoundPlayers);
	if(FoundPlayers.Num())
	{
		Player1 = CastChecked<APlayer2DCharacter>(FoundPlayers[0]); //Fix later
	}
	else
		Debug::ErrorMessage("Game state unable to find any player characters in %s", __FUNCTION__);
}

void ATheyMustDieGameState::ResetPlayerReferences()
{
	Player1.Reset();
	Player2.Reset();
	Player3.Reset();
	Player4.Reset();
}

void ATheyMustDieGameState::GetRelicReference()
{
	TArray<AActor*> FoundBuildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildingActor::StaticClass(), FoundBuildings);
	if(FoundBuildings.Num())
	{
		SacredRelic = CastChecked<ABuildingActor>(FoundBuildings[0]); //Fix later
	}
	else
		Debug::ErrorMessage("Game state unable to find any buildings in %s", __FUNCTION__);
}

void ATheyMustDieGameState::ResetRelicReference()
{
	SacredRelic.Reset();
}

void ATheyMustDieGameState::StopAllCharacterLogic()
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaper2DCharacter::StaticClass(), FoundCharacters);
	for(int i = 0; i < FoundCharacters.Num(); ++i)
	{
		APaper2DCharacter *Char = CastChecked<APaper2DCharacter>(FoundCharacters[i]);
		if(Char)
		{
			Char->StopCharacterLogic();
			Char->Disable();
		}
	}

}
