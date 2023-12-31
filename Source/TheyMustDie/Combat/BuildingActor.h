// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BuildingActor.generated.h"

//Actor type used for all buildings in the game
UCLASS()
class THEYMUSTDIE_API ABuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuildingActor();

	//Applies physical damage to this building actor
	void ApplyPhysicalDamage(unsigned int Damage);

	//Returns true if this building has been destroyed, false if not
	bool isDestroyed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The current hit points of this building
	UPROPERTY(EditAnywhere)
	uint32 HP;

	//The max hit points of this building
	UPROPERTY(EditAnywhere)
	uint32 MaxHP;

	//True if this building has been destroyed, ie HP is 0
	UPROPERTY(VisibleAnywhere)
	bool Destroyed;

	//The physical armor of this building
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Physical Armor"))
	signed int PhysArmor;

	//The magical armor of this building
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Magical Armor"))
	signed int MagicArmor;

	//The box component serving as the hit box for this building.
	UPROPERTY(VisibleAnywhere)
	UBoxComponent *BuildingHitBox;

	//Function called when another actor overlaps with this building.
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
