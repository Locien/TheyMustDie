// ©Kris and Tashhhh 2023

#include "ProjectileComponent.h"
#include "../Debug.h"
#include "../Character/Player2DCharacter.h"
#include "../Character/Enemy2DCharacter.h"
#include "Kismet/GameplayStatics.h"

UProjectileComponent::UProjectileComponent()
{
	SetCollisionProfileName("ProjectileCollision");
	SetGenerateOverlapEvents(false); //Set this to true after firing the projectile, spawning it into the world and after calling SetOwningActor() so overlap events happen when OwningActor is valid.
}

void UProjectileComponent::SetOwningActor(AActor *OwnerActor)
{
	OwningActor = OwnerActor;
}

void UProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	this->OnComponentHit.AddDynamic(this, &UProjectileComponent::OnHit);
	this->OnComponentBeginOverlap.AddDynamic(this, &UProjectileComponent::OnOverlap);
	GetOwner()->SetLifeSpan(20.f);
}

void UProjectileComponent::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	GetOwner()->Destroy();
}

void UProjectileComponent::OnOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor->IsA(AEnemy2DCharacter::StaticClass()))
	{
		AEnemy2DCharacter *Enemy = Cast<AEnemy2DCharacter>(OtherActor);
		if(Enemy != nullptr)
		{
			if(!Enemy->isFriendly() && Enemy->isAlive())
			{
				if(OwningActor.IsValid() && OwningActor.Get()->IsA(APlayer2DCharacter::StaticClass()))
				{
					APlayer2DCharacter *Player = CastChecked<APlayer2DCharacter>(OwningActor.Get());
					Enemy->ApplyPhysicalDamage(Player->GetCharacterStats()->GetPhysAttack());
					Enemy->SetAngry(true);
					GetOwner()->Destroy();
				}
			}
		}
		else
			Debug::ErrorMessage("Unable to cast overlapped actor to AEnemy2DCharacter in %s", __FUNCTION__);
	}
}


