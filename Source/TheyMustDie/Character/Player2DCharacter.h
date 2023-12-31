// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Paper2DCharacter.h"
#include "PaperFlipbookComponent.h"
#include "CineCameraComponent.h"
#include "../Combat/ProjectileComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player2DCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API APlayer2DCharacter : public APaper2DCharacter
{
	GENERATED_BODY()

public:
	APlayer2DCharacter();

	//Gets the player ID of this player character
	int GetPlayerCharacterID();

	//Makes this player character receive experience points.
	void ReceiveExperience(unsigned int ExpPts);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Perform Player Attack", Keywords = "player perform attack"), Category = "TheyMustDie")
	void PerformAttack();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Player HP Text", Keywords = "player get HP text"), Category = "TheyMustDie")
	FText GetHPText();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Player Level Text", Keywords = "player get level text"), Category = "TheyMustDie")
	FText GetLvlText();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Player Experience Text", Keywords = "player get experience text"), Category = "TheyMustDie")
	FText GetExpText();

protected:
	//Called once after components have been initialized
	virtual void PostInitializeComponents() override;

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Function called when another actor overlaps with this character.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//Sets the projectile class for firing during attacks. Must be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileClass;

	//The camera spring arm associated with this player character
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraSpringArm;

	//The camera component of this player character
	UPROPERTY(EditAnywhere)
	UCineCameraComponent* CameraComponent;

	//The player ID of this player character
	int PlayerCharacterID;

	//The level of this character
	unsigned int Level;

	//The current experience points of this character
	unsigned int Exp;

private:
	//Function called when this player levels up
	void OnLevelUp();
};
