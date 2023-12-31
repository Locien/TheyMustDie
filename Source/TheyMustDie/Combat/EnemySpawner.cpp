// ©Kris and Tashhhh 2023


#include "EnemySpawner.h"
#include "TimerManager.h"
#include "../Debug.h"

//Sets default values
AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Direction = ESpawnerDirectionality::SPAWN_ON_SPAWNER;

	EnemyType1 = nullptr;
	EnemyType2 = nullptr;

	EnemySpawnRate1 = 5.0f;
	EnemySpawnRate2 = 5.0f;
	EnemyAmount1 = 1;
	EnemyAmount2 = 1;
	EnemyTotalAmount1 = -1;
	EnemyTotalAmount2 = -1;
	Distance = 500.F;
}

//Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if(EnemyType1)
	{
		if(EnemyTotalAmount1 < 0 || NumSpawnedEnemy1 < (unsigned int)EnemyTotalAmount1)
			SpawnEnemyType1();
	}
	else
		Debug::ErrorMessage("Enemy type #1 in enemy spawner returned nullptr, make sure it's set in the editor");
}

void AEnemySpawner::SpawnEnemyType1()
{
	switch(Direction)
	{
		case ESpawnerDirectionality::SPAWN_ON_SPAWNER:
		{
			SpawnEnemyOnSpawner(EnemyType1, 1);
			break;
		}

		case ESpawnerDirectionality::SPAWN_X_AXIS:
		{
			SpawnEnemyOnXAxis(EnemyType1, 1);
			break;
		}

		case ESpawnerDirectionality::SPAWN_Y_AXIS:
		{
			SpawnEnemyOnYAxis(EnemyType1, 1);
			break;
		}

		default:
		{
			Debug::ErrorMessage("Unknown spawner directionality set in %s", __FUNCTION__);
		}
	}


	if(EnemyTotalAmount1 < 0 || NumSpawnedEnemy1 < (unsigned int)EnemyTotalAmount1)
		GetWorldTimerManager().SetTimer(EnemyTimerHandle1, this, &AEnemySpawner::SpawnEnemyType1, EnemySpawnRate1);
	else
	{

	}
}

//Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::StopSpawner()
{
	GetWorldTimerManager().ClearTimer(EnemyTimerHandle1);
	GetWorldTimerManager().ClearTimer(EnemyTimerHandle2);
}

void AEnemySpawner::ResetSpawner(UPARAM(DisplayName = "Restart")bool Restart)
{
	NumSpawnedEnemy1 = 0;
	NumSpawnedEnemy2 = 0;
}

void AEnemySpawner::SpawnEnemyOnSpawner(const TSubclassOf<AEnemy2DCharacter> &EnemyType, const unsigned char EnemyNumber)
{
	FVector Location = GetActorLocation();
	AEnemy2DCharacter* Enemy = GetWorld()->SpawnActor<AEnemy2DCharacter>(EnemyType, FVector(Location.X, Location.Y, 15.F), FRotator(0.F));

	if(EnemyNumber == 1)
		NumSpawnedEnemy1++;
	else if(EnemyNumber == 2)
		NumSpawnedEnemy2++;
}

void AEnemySpawner::SpawnEnemyOnXAxis(const TSubclassOf<AEnemy2DCharacter> &EnemyType, const unsigned char EnemyNumber)
{
	int NumEnemies = 0;
	if(EnemyNumber == 1)
	{
		NumEnemies = EnemyAmount1;
		NumSpawnedEnemy1 += NumEnemies;
	}
	else if(EnemyNumber == 2)
	{
		NumEnemies = EnemyAmount2;
		NumSpawnedEnemy2 += NumEnemies;
	}

	FVector StartLocation = GetActorLocation() - FVector(Distance, 0, 0);
	StartLocation.Z = 15.F;
	double SeparationDistance = (Distance*2.F)/(double)NumEnemies;

	for(int i = 0; i < NumEnemies; i++)
	{
		AEnemy2DCharacter* Enemy = GetWorld()->SpawnActor<AEnemy2DCharacter>(EnemyType, StartLocation + FVector(SeparationDistance*(double)i, 0, 0), FRotator(0.F));
	}
}

void AEnemySpawner::SpawnEnemyOnYAxis(const TSubclassOf<AEnemy2DCharacter>& EnemyType, const unsigned char EnemyNumber)
{
	int NumEnemies = 0;
	if (EnemyNumber == 1)
	{
		NumEnemies = EnemyAmount1;
		NumSpawnedEnemy1 += NumEnemies;
	}
	else if (EnemyNumber == 2)
	{
		NumEnemies = EnemyAmount2;
		NumSpawnedEnemy2 += NumEnemies;
	}

	FVector StartLocation = GetActorLocation() - FVector(0, Distance, 0);
	StartLocation.Z = 15.F;
	double SeparationDistance = (Distance*2.F) / (double)NumEnemies;

	for (int i = 0; i < NumEnemies; i++)
	{
		AEnemy2DCharacter* Enemy = GetWorld()->SpawnActor<AEnemy2DCharacter>(EnemyType, StartLocation + FVector(0, SeparationDistance*(double)i, 0), FRotator(0.F));
	}
}


