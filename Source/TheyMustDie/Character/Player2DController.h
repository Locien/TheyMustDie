// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Player2DCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Player2DController.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API APlayer2DController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayer2DController();

	//Attempts to possess a given player character.
	void PossessPlayerCharacter(APlayer2DCharacter *PlayerCharacter);

protected:
	//Function that ticks every frame of the game
	virtual void PlayerTick(float DeltaTime) override;

	//Sets up the input component responsible for listening for action and axis mappings
	virtual void SetupInputComponent() override;

	//Called after receiving a player
	virtual void ReceivedPlayer() override;

	//Sets the forward movement axis of this player
	void SetForwardAxis(float Axis);

	//Sets the right movement axis of this player
	void SetRightAxis(float Axis);

	//Function called when the tab key is pressed down
	void OnTabDown();

	//Function called when the left mouse button is pressed down.
	void OnLeftMouseDown();

	//Function called when the left mouse button is released.
	void OnLeftMouseUp();

	//Function called when the left mouse button is pressed down.
	void OnRightMouseDown();

	//Function called when the left mouse button is released.
	void OnRightMouseUp();

	//The currently possessed character. May be empty, check before dereferencing.
	UPROPERTY(EditAnywhere)
	APlayer2DCharacter *PossessedCharacter;
	
};
