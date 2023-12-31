// ©Kris and Tashhhh 2023

#include "Player2DCharacter.h"
#include "Enemy2DCharacter.h"
#include "PaperFlipbook.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Blueprint/UtilityBlueprints.h"
#include "../UI/DamageDisplayer.h"
#include "../Debug.h"
#include <string>

APlayer2DCharacter::APlayer2DCharacter()
{
	CameraSpringArm = nullptr;

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->SetUsingAbsoluteRotation(true);
	CameraSpringArm->TargetArmLength = 500.f;
	CameraSpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	CameraSpringArm->bDoCollisionTest = false;

	GetCapsuleComponent()->SetCollisionProfileName("PlayerCollision"); //Player collision preset.
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	CameraComponent = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Camera"));

	CameraComponent->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	GetCharacterMovement()->MaxWalkSpeed = 200.f; //Base movement speed

	CharacterStats = new CharacterCommonStats(100, 100, 10, 10, 30, 10, true);
	Level = 1;
	Exp = 0;

	CharHitBox->SetBoxExtent(FVector(10.F, 12.F, 12.F), true);
	AttackHitBox->SetBoxExtent(FVector(20.F, 12.F, 12.F), true);
	AttackHitBox->SetRelativeLocation(FVector(10.F, 0.F, 0.F));

	Friendly = true; //This is a friendly unit
	SetTicking(true); //Set the unit to tick every frame for movement logic, et.c.

	//Fix this later when it's possible to have multiple player characters
	PlayerCharacterID = 0;
}

int APlayer2DCharacter::GetPlayerCharacterID()
{
	return PlayerCharacterID;
}

void APlayer2DCharacter::ReceiveExperience(unsigned int ExpPts)
{
	Exp += ExpPts;
	if(Exp >= (100+(Level*50)-50))
	{
		Exp -= (100+(Level*50)-50);
		OnLevelUp();
	}
}

void APlayer2DCharacter::PerformAttack()
{
	if(ProjectileClass.Get() != nullptr)
	{
		FVector CurrentLocation = GetActorLocation();
		FWorldContext Context = GEngine->GetWorldContexts().Last();
		UWorld *World = Context.World();
		if(World != nullptr)
		{
			APlayerController *PlayerController = GEngine->GetFirstLocalPlayerController(World);
			if(PlayerController != nullptr)
			{
				FHitResult HitResult;
				PlayerController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true, HitResult); //Custom trace channel for floor only
				FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, HitResult.ImpactPoint);
				Rotation.Pitch = 0;
				AActor *Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, FVector(CurrentLocation.X, CurrentLocation.Y, 15.F), Rotation);
				UProjectileComponent *ProjectileComp = Cast<UProjectileComponent>(Projectile->GetRootComponent());
				ProjectileComp->SetOwningActor(this);
				ProjectileComp->SetGenerateOverlapEvents(true);
			}
		}
	}
}

FText APlayer2DCharacter::GetHPText()
{
	if(CharacterStats != nullptr)
	{
		std::string HPText = std::to_string(CharacterStats->GetHP()) +  "/" + std::to_string(CharacterStats->GetMaxHP());
		return FText::FromString(FString(HPText.c_str()));
	}
	else
		return FText::FromString(FString("NULL/NULL"));
}

FText APlayer2DCharacter::GetLvlText()
{
	std::string Lvl = std::to_string(Level);
	return FText::FromString(FString(Lvl.c_str()));
}

FText APlayer2DCharacter::GetExpText()
{
	std::string ExpText = std::to_string(Exp) + "/" + std::to_string(100+(Level*50)-50);
	return FText::FromString(FString(ExpText.c_str()));
}

void APlayer2DCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetSprite()->SetCastShadow(true);
}

void APlayer2DCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayer2DCharacter::OnOverlapBegin);

}

void APlayer2DCharacter::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(AEnemy2DCharacter::StaticClass()) && OtherComp->GetCollisionProfileName() == "EnemyCollision")
	{
		AEnemy2DCharacter *Enemy = Cast<AEnemy2DCharacter>(OtherActor);
		if(Enemy != nullptr && Enemy->isAlive())
		{
			Enemy->UseBaseAttack(this); //Take base damage from enemy when you overlap with their capsule component
		}
	}
	
}

void APlayer2DCharacter::OnLevelUp()
{
	Level++;
	signed int CurrentMaxHP = CharacterStats->GetMaxHP();
	CharacterStats->SetMaxHP(CurrentMaxHP+20, true);
	signed int CurrentPhysAtk = CharacterStats->GetPhysAttack();
	CharacterStats->SetPhysAttack(CurrentPhysAtk+5);
}
