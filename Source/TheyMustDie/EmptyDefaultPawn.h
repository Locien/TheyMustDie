// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EmptyDefaultPawn.generated.h"

UCLASS()
class THEYMUSTDIE_API AEmptyDefaultPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEmptyDefaultPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
