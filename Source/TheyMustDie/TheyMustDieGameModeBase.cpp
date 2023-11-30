// Copyright Epic Games, Inc. All Rights Reserved.


#include "TheyMustDieGameModeBase.h"
#include "Character/Player2DController.h"
#include "TheyMustDieGameState.h"
#include "EmptyDefaultPawn.h"

ATheyMustDieGameModeBase::ATheyMustDieGameModeBase()
{
	PlayerControllerClass = APlayer2DController::StaticClass();
	DefaultPawnClass = AEmptyDefaultPawn::StaticClass();
	GameStateClass = ATheyMustDieGameState::StaticClass();
}