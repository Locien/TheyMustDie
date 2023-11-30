// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Paper2DCharacter.h"
#include "Enemy2DCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API AEnemy2DCharacter : public APaper2DCharacter
{
	GENERATED_BODY()

public:
	AEnemy2DCharacter();

	//Applies base attack damage on a specified character.
	void UseBaseAttack(APaper2DCharacter *Target);

	//Applies physical attack damage to players and buildings within the hitbox radius.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Use Enemy Melee Attack", Keywords = "use enemy melee attack"), Category = "TheyMustDie")
	void UseMeleeAttack();

	//Performs a basic melee attack, make sure UseMeleeAttack() is called in animation blueprint notifies to release the attack.
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Perform Enemy Attack", Keywords = "enemy perform attack"), Category = "TheyMustDie")
	void PerformAttack();

protected:
	//Called once after components have been initialized
	virtual void PostInitializeComponents() override;

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when this enemy dies.
	virtual void OnDeath() override;

	//The amount of experience points that this enemy will award the player upon death
	UPROPERTY(VisibleAnywhere)
	uint32 ExperiencePoints;
	
};
