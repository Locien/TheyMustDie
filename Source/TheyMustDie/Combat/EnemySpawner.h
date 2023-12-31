// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Character/Enemy2DCharacter.h"
#include "EnemySpawner.generated.h"

//Sets the directionality of this spawner, ie where the enemies should be spawned from
UENUM(BlueprintType)
enum class ESpawnerDirectionality : uint8 {
	//Spawns enemies on top of the spawner, this setting will only spawn one enemy at a time
	SPAWN_ON_SPAWNER	UMETA(DisplayName = "On Spawner"),
	//Spawns enemies spread out in the X-axis 
	SPAWN_X_AXIS		UMETA(DisplayName = "X-axis"),
	//Spawns enemies spread out in the Y-axis
	SPAWN_Y_AXIS		UMETA(DisplayName = "Y-axis"),
	//Spawns enemies spread out in a radius around the spawner
	SPAWN_RADIUS		UMETA(DisplayName = "Radius"),
};

UCLASS()
class THEYMUSTDIE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	//Sets default values for this actor's properties
	AEnemySpawner();

	//Sets the enemy type to spawn from this spawner. Must be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	TSubclassOf<AEnemy2DCharacter> EnemyType1;

	//Sets the enemy type 1 spawn rate for this spawner in seconds. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	float EnemySpawnRate1;

	//Sets the the amount of enemy type 1 to spawn each tick. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	uint32 EnemyAmount1;

	//Sets the the total amount of enemy type 1 to spawn, if -1 it will spawn endlessly. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	int EnemyTotalAmount1;

	//The timer handle responsible for keeping track of the spawning of enemy type 1
	FTimerHandle EnemyTimerHandle1;

	//Sets an additional enemy type to spawn from this spawner. Must be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	TSubclassOf<AEnemy2DCharacter> EnemyType2;

	//Sets the enemy type 2 spawn rate for this spawner in seconds. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	float EnemySpawnRate2;

	//Sets the the amount of enemy type 2 to spawn each tick. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	uint32 EnemyAmount2;

	//Sets the the total amount of enemy type 2 to spawn, if -1 it will spawn endlessly. Can be assigned in editor.
	UPROPERTY(EditDefaultsOnly, Category = "Enemies")
	int EnemyTotalAmount2;

	//The timer handle responsible for keeping track of the spawning of enemy type 2
	FTimerHandle EnemyTimerHandle2;

protected:
	//Enum specifying which direction that this spawner will spread out its spawned enemies in.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpawnerDirectionality Direction;

	//The maximum distance at which enemies will spawn away from the spawner. If the spawner is circular this value becomes the radius.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Distance;

	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Spawns enemy type 1 into the game world
	void SpawnEnemyType1();

public:	
	//Called every frame
	virtual void Tick(float DeltaTime) override;

	//Stops this spawner from spawning any enemies
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Stop Spawner", Keywords = "stop spawner"), Category = "TheyMustDie")
	void StopSpawner();

	//Resets this spawner to count as having spawned no enemies, if bool Restart is set to true it will also restart the spawner
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Stop Spawner", Keywords = "stop spawner"), Category = "TheyMustDie")
	void ResetSpawner(UPARAM(DisplayName = "Restart")bool Restart = true);

private:
	//Spawns a given enemy on top of the spawner, only allows for one spawn at a time
	void SpawnEnemyOnSpawner(const TSubclassOf<AEnemy2DCharacter> &EnemyType, const unsigned char EnemyNumber);

	//Spawns a given enemy spread out in the X axis
	void SpawnEnemyOnXAxis(const TSubclassOf<AEnemy2DCharacter>& EnemyType, const unsigned char EnemyNumber);

	//Spawns a given enemy spread out in the Y axis
	void SpawnEnemyOnYAxis(const TSubclassOf<AEnemy2DCharacter>& EnemyType, const unsigned char EnemyNumber);

	//The number of enemy 1 that has spawned so far. Can be reset by calling ResetSpawner().
	uint32 NumSpawnedEnemy1;

	//The number of enemy 2 that has spawned so far. Can be reset by calling ResetSpawner().
	uint32 NumSpawnedEnemy2;

};
