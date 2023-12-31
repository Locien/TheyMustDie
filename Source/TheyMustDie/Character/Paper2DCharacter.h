// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "PaperZDCharacter.h"
#include "CharacterCommonStats.h"
#include "Components/BoxComponent.h"
#include "Paper2DCharacter.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API APaper2DCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	APaper2DCharacter();
	~APaper2DCharacter();

	//Sets the forward movement axis of this character
	void SetForwardAxis(float Axis);

	//Sets the right movement axis of this character
	void SetRightAxis(float Axis);

	//Sets PrimaryActorTick.bCanEverTick component which makes this character tick every frame
	void SetTicking(bool Ticking);

	//Attempts to move this character in the forward-backwards direction using a float axis value
	void MoveForward(float Axis);

	//Attempts to move this character in the right-left direction using a float axis value
	void MoveRight(float Axis);

	//Applies physical damage to this character.
	void ApplyPhysicalDamage(unsigned int Damage);

	//Returns true if this character is able to move, false if not
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Can Move", Keywords = "player paper character can move"), Category = "TheyMustDie")
	bool CanMove();

	//Returns true if this character is able to attack, false if not
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Can Attack", Keywords = "player paper character can attack"), Category = "TheyMustDie")
	bool CanAttack();

	//Returns true if this character is able to rotate, false if not
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Can Rotate", Keywords = "player paper character can rotate"), Category = "TheyMustDie")
	bool CanRotate();

	//Returns true if this character is currently walking, false if not walking
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character is Walking", Keywords = "player paper character is walking"), Category = "TheyMustDie")
	bool isWalking();

	//Sets the walking flag for this character to given boolean
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Paper Character Set Walking", Keywords = "player paper character set walking"), Category = "TheyMustDie")
	void SetWalking(bool Walking);

	//Returns a const reference to the rotation vector of this character
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Get Rotation Vector", Keywords = "player paper character get rotation vector"), Category = "TheyMustDie")
	const FVector2D &GetRotationVector();

	//Sets the rotation vector of this character
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Set Rotation Vector", Keywords = "player paper character set rotation vector"), Category = "TheyMustDie")
	void SetRotationVector(UPARAM(DisplayName = "Rotation")const FVector2D &Rotation);

	//Sets the rotation vector of this character and returns this value. This is an abomination of a function used in monster animation blueprints
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character Set and Return Rotation Vector", Keywords = "player paper character set and return rotation vector"), Category = "TheyMustDie")
	const FVector2D &SetAndReturnRotationVector(UPARAM(DisplayName = "Rotation")const FVector2D& Rotation);

	//Returns true if this character is currently walking, false if not walking
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character is Alive", Keywords = "player paper character is alive"), Category = "TheyMustDie")
	bool isAlive();

	//Returns true if this character is a friendly unit, false otherwise
	bool isFriendly();

	//Sets the attacking flag for this character to given boolean
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Paper Character Set Attacking", Keywords = "player paper character set attacking"), Category = "TheyMustDie")
	void SetAttacking(UPARAM(DisplayName = "Attacking")bool Attacking);

	//Returns true if this character is currently attacking, false if not attacking
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Paper Character is Attacking", Keywords = "player paper character is attacking"), Category = "TheyMustDie")
	bool isAttacking();

	//Stops the movement and AI logic of this character if it's AI controlled.
	void StopCharacterLogic();

	//Disables this character from being controlled by a player in any way.
	void Disable();

	//Gets a pointer to this character's status.
	CharacterCommonStats *GetCharacterStats();

protected:
	//Function that ticks every frame of the game
	virtual void Tick(float DeltaTime) override;

	//Common character stats that are used by all player and enemy characters
	CharacterCommonStats *CharacterStats;

	//Movement vector input as supplied by the player controller in the event that a player is controlling this character
	UPROPERTY(VisibleAnywhere)
	FVector2D MovementVector;

	//The rotation vector of this character which depends on which direction it is moving in or attacking in
	UPROPERTY(VisibleAnywhere)
	FVector2D RotationVector;

	//The box component serving as the hitbox for this character.
	UPROPERTY(VisibleAnywhere)
	UBoxComponent *CharHitBox;

	//The box component serving as the melee attack hitbox for this character.
	UPROPERTY(VisibleAnywhere)
	UBoxComponent *AttackHitBox;

	//Sets the sound cue to be played when this character takes damage. Assign in editor, can be left null though.
	UPROPERTY(EditDefaultsOnly, Category = "Sound Effects")
	USoundCue *DamageSFX;

	//True if this character is a friendly unit, false otherwise
	UPROPERTY(EditAnywhere)
	bool Friendly;
	//True if this character is walking, false otherwise
	UPROPERTY(EditAnywhere)
	bool Walking;
	//True if this character is currently attacking, false otherwise
	UPROPERTY(EditAnywhere)
	bool Attacking;
	//True if this character is alive, false otherwise
	UPROPERTY(EditAnywhere)
	bool Alive;
	//True if this character is disabled, false otherwise
	UPROPERTY(EditAnywhere)
	bool Disabled;

	//Called when this character dies.
	virtual void OnDeath();

	//Called when this character takes damage of any kind.
	virtual void OnDamageTaken(unsigned int DamageTaken);
};
