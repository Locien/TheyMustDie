// ©Kris and Tashhhh 2023


#include "EmptyDefaultPawn.h"

// Sets default values
AEmptyDefaultPawn::AEmptyDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEmptyDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmptyDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEmptyDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

