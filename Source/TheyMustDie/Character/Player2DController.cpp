// ©Kris and Tashhhh 2023


#include "Player2DController.h"
#include "Engine/Engine.h"

APlayer2DController::APlayer2DController()
{
	PossessedCharacter = nullptr;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	bShowMouseCursor = true;
}

void APlayer2DController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void APlayer2DController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Set up action bindings for attacking, menus, et.c
	InputComponent->BindAction("TabKey", IE_Pressed, this, &APlayer2DController::OnTabDown);
	InputComponent->BindAction("LeftClick", IE_Pressed, this, &APlayer2DController::OnLeftMouseDown);
	InputComponent->BindAction("LeftClick", IE_Released, this, &APlayer2DController::OnLeftMouseUp);
	InputComponent->BindAction("RightClick", IE_Pressed, this, &APlayer2DController::OnRightMouseDown);
	InputComponent->BindAction("RightClick", IE_Released, this, &APlayer2DController::OnRightMouseUp);

	//Set up axis bindings for movement
	InputComponent->BindAxis("MoveForward", this, &APlayer2DController::SetForwardAxis);
	InputComponent->BindAxis("MoveRight", this, &APlayer2DController::SetRightAxis);

}

void APlayer2DController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
}

void APlayer2DController::PossessPlayerCharacter(APlayer2DCharacter* PlayerCharacter)
{
	Possess(PlayerCharacter);
	PossessedCharacter = PlayerCharacter;
}

void APlayer2DController::SetForwardAxis(float Axis)
{
	if(PossessedCharacter != nullptr)
		PossessedCharacter->SetForwardAxis(Axis);
}

void APlayer2DController::SetRightAxis(float Axis)
{
	if(PossessedCharacter != nullptr)
		PossessedCharacter->SetRightAxis(Axis);
}

void APlayer2DController::OnTabDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Tab key pressed"));
}

void APlayer2DController::OnLeftMouseDown()
{
	if(PossessedCharacter != nullptr)
	{
		PossessedCharacter->SetAttacking(true);
	}
}

void APlayer2DController::OnLeftMouseUp()
{
	if(PossessedCharacter != nullptr)
	{
		PossessedCharacter->SetAttacking(false);
	}
}

void APlayer2DController::OnRightMouseDown()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Right mouse button pressed"));
}

void APlayer2DController::OnRightMouseUp()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Right mouse button released"));
}
