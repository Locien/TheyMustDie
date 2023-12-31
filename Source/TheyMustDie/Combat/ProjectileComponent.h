// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileComponent.generated.h"

/**
 *  Class to serve as a static mesh for projectiles which will call void OnHit on impact
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEYMUSTDIE_API UProjectileComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UProjectileComponent();

	//Sets the owning actor of this projectile component.
	void SetOwningActor(AActor *OwnerActor);

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The actor who owns this projectile, check if the pointer is valid before derferencing
	UPROPERTY(VisibleAnywhere)
	TWeakObjectPtr<AActor> OwningActor;

	//Function called when this projectile collides with something
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	//Function called when this projectile overlaps with a hitbox
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

};
