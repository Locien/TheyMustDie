// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Combat/BuildingActor.h"
#include "Character/Player2DCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "TheyMustDieGameState.generated.h"

//Enums specifying which type of game over has happened
enum GameOverTypeT
{
	NOT_GAME_OVER, //Initial value
	GAME_OVER_WIN, //Players won the game
	GAME_OVER_PLAYER_DEAD,
	GAME_OVER_PARTY_DEAD,
	GAME_OVER_RELIC_DESTROYED,
};

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API ATheyMustDieGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATheyMustDieGameState();

	//Starts the game logic run on the game state
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Start Game", Keywords = "start game"), Category = "TheyMustDie")
	static void StartGame();

	//Ends the game logic run on the game state
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "End Game", Keywords = "end game"), Category = "TheyMustDie")
	static void EndGame();

	//Returns true if the game is running on the game state, returns false if it's not running
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Game Running", Keywords = "is game running"), Category = "TheyMustDie")
	static bool isGameRunning();

	//Returns a text string showing a message displayed under the game over decal depending on why the player(s) lost
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Game Over Text", Keywords = "get game over text"), Category = "TheyMustDie")
	static FText GetGameOverText();

protected:
	//Function that ticks every frame and deals with game state updates and checks
	virtual void Tick(float Deltatime) override;

	//Called when all players are dead or the sacred relic has been destroyed
	void OnGameOver();

	//Reference to player character 1, check if the pointer is valid before dereferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<APlayer2DCharacter> Player1;

	//Reference to player character 2, check if the pointer is valid before dereferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<APlayer2DCharacter> Player2;

	//Reference to player character 3, check if the pointer is valid before dereferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<APlayer2DCharacter> Player3;

	//Reference to player character 4, check if the pointer is valid before dereferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<APlayer2DCharacter> Player4;

	//Reference to the sacred relic building, check if pointer is valid before dereferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<ABuildingActor> SacredRelic;

	//The user widget to display on game over
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UUserWidget> GameOverWidget;

private:
	//A self referencing static pointer to the current game state
	static ATheyMustDieGameState *Self;

	//True if the game has started and is running, false if not.
	bool GameRunning;

	//Checks if the lose condition has been fulfilled
	void ProcessLoseCondition();

	//Attempts to find player characters and assign them to the player character references.
	void GetPlayerReferences();

	//Resets all player character references.
	void ResetPlayerReferences();

	//Attempts to get a reference to the sacred relic building.
	void GetRelicReference();

	//Resets the reference to the sacred relic building.
	void ResetRelicReference();

	//Stops the logic of all characters in the game.
	void StopAllCharacterLogic();

	//The game over type in the even that the game has ended
	GameOverTypeT GameOverType;
	
};
