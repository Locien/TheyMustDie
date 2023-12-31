// ©Kris and Tashhhh 2023


#include "BuildingActor.h"
#include "../Debug.h"
#include "../Character/CharacterCommonStats.h"
#include "../Character/Enemy2DCharacter.h"
#include "../Combat/AttackHitboxComponent.h"
#include "../UI/DamageDisplayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/MeshComponent.h"

//Sets default values
ABuildingActor::ABuildingActor()
{
	PrimaryActorTick.bCanEverTick = false;
	HP = 100;
	MaxHP = 100;
	PhysArmor = 10;
	MagicArmor = 10;
	Destroyed = false;

	BuildingHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BuildingHitBox"));
	BuildingHitBox->SetComponentTickEnabled(false);
	BuildingHitBox->SetupAttachment(RootComponent);
}

void ABuildingActor::ApplyPhysicalDamage(unsigned int Damage)
{
	if(HP) //Check to make sure building isn't already destroyed
	{
		unsigned int TakenDmg = ((signed int)Damage - (signed int)PhysArmor < 0) ? 0 : Damage-PhysArmor; //Clamp damage to zero so we don't get any underflows.
		if((signed int)HP - (signed int)TakenDmg < 0) //Same with HP
			HP = 0;
		else
			HP -= TakenDmg;
		UDamageDisplayer* DamageText = CreateWidget<UDamageDisplayer>(GetWorld(), UDamageDisplayer::StaticClass());
		DamageText->LaunchDamageText(TakenDmg, FLinearColor(1.f, 0.f, 0.f, 1.f), GetActorLocation());

		if(HP == 0)
		{
			Destroyed = true;
			UGameplayStatics::ApplyDamage(this, 1000.f, GetInstigatorController(), this, UDamageType::StaticClass()); //Sets off the destruction physics if this building has any
		}
	}
}

bool ABuildingActor::isDestroyed()
{
	return Destroyed;
}

// Called when the game starts or when spawned
void ABuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
	BuildingHitBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildingActor::OnOverlapBegin);

}

void ABuildingActor::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor->IsA(AEnemy2DCharacter::StaticClass()))
	{
		AEnemy2DCharacter *Enemy = CastChecked<AEnemy2DCharacter>(OtherActor);
		if(!Enemy->isFriendly() && OtherComp->IsA(UAttackHitboxComponent::StaticClass()))
		{
			ApplyPhysicalDamage((unsigned int)Enemy->GetCharacterStats()->GetPhysAttack());
		}
	}
}

// Called every frame
void ABuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

