// ©Kris and Tashhhh 2023


#include "Enemy2DCharacter.h"
#include "Player2DCharacter.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Debug.h"

AEnemy2DCharacter::AEnemy2DCharacter()
{
	Friendly = false; //This is an enemy unit
	CharacterStats = new CharacterCommonStats(100, 100, 5, 5, 20, 20, true);

	GetCapsuleComponent()->SetCollisionProfileName("EnemyCollision"); //Player collision preset.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	ExperiencePoints = 10;
	GetCharacterMovement()->MaxWalkSpeed = 100.f; //Base movement speed

	Angry = false;
}

void AEnemy2DCharacter::UseMeleeAttack()
{
	if(CanAttack())
	{
		AttackHitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AEnemy2DCharacter::PerformAttack()
{
	if(CanAttack() && !Attacking)
	{
		SetAttacking(true);
	}
}

void AEnemy2DCharacter::SetAngry(bool Anger)
{
	Angry = Anger;
}

bool AEnemy2DCharacter::isAngry()
{
	return Angry;
}

void AEnemy2DCharacter::UseBaseAttack(APaper2DCharacter *Target)
{
	if(CanAttack())
	{
		Target->ApplyPhysicalDamage(CharacterStats->GetPhysAttack());
	}
}

void AEnemy2DCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetSprite()->SetCastShadow(true);
}

void AEnemy2DCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy2DCharacter::OnDeath()
{
	Super::OnDeath();

	TArray<AActor*> FoundPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayer2DCharacter::StaticClass(), FoundPlayers);
	APlayer2DCharacter *Player = Cast<APlayer2DCharacter>(FoundPlayers[0]);
	Player->ReceiveExperience(ExperiencePoints);
	SetLifeSpan(5.f); //Expire in 5 seconds
}
