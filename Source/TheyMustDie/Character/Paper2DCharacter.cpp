// ©Kris and Tashhhh 2023


#include "Paper2DCharacter.h"
#include "BrainComponent.h"
#include "AIController.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "../Combat/AttackHitboxComponent.h"
#include "../UI/DamageDisplayer.h"
#include "../Debug.h"

APaper2DCharacter::APaper2DCharacter()
{
	//Set initial capsule size
	GetCapsuleComponent()->InitCapsuleSize(15.f, 15.0f);
	RootComponent = GetCapsuleComponent();

	CharacterStats = nullptr;
	DamageSFX = nullptr;

	//All characters should be rotated 90° in the Z axis/yaw.
	SetActorRotation(FRotator(0.F, 90.F, 0.F));

	//Prevents characters from rotating around themselves.
	bUseControllerRotationYaw = false;

	Attacking = false;
	Walking = false;
	Friendly = false;
	Disabled = false;
	Alive = true;

	MovementVector = FVector2D(0.F, 0.F);
	RotationVector = FVector2D(0.F, -1.0F);

	GetCharacterMovement()->bRequestedMoveUseAcceleration = 0; //Makes movement instant.

	CharHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CharHitBox"));
	CharHitBox->SetComponentTickEnabled(false);
	CharHitBox->SetupAttachment(RootComponent);

	AttackHitBox = CreateDefaultSubobject<UAttackHitboxComponent>(TEXT("AttackHitBox"));
	AttackHitBox->SetComponentTickEnabled(false);
	AttackHitBox->SetCollisionProfileName("AttackCollision");
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision); //Turn off the collision by default and enable it as it needs to be active.
	AttackHitBox->SetupAttachment(RootComponent);

	//Ticking is set to false by default so enemy characters don't all tick.
	PrimaryActorTick.bCanEverTick = false;
}

APaper2DCharacter::~APaper2DCharacter()
{
	if(CharacterStats != nullptr)
		delete CharacterStats;
}

void APaper2DCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Friendly)
	{
		if((MovementVector.X > 0.01F || MovementVector.X < 0.F))
		{
			if(CanRotate())
				RotationVector = FVector2D(0.F); //Reset the rotation vector

			MoveForward(MovementVector.X);
			if(MovementVector.Y > 0.01F || MovementVector.Y < 0.F)
				MoveRight(MovementVector.Y);
		}
		else if(MovementVector.Y > 0.01F || MovementVector.Y < 0.F)
		{
			if(CanRotate())
				RotationVector = FVector2D(0.F); //Reset the rotation vector

			MoveRight(MovementVector.Y);
		}
		else
			Walking = false;
	}
}

void APaper2DCharacter::MoveForward(float Axis)
{
	if(CanMove())
	{
		Walking = true;
		AddMovementInput(FVector(1.0F, 0.F, 0.F), Axis);
		if(CanRotate())
			RotationVector.Y = Axis;
	}
	else
		Walking = false;
}

void APaper2DCharacter::MoveRight(float Axis)
{
	if(CanMove())
	{
		Walking = true;
		AddMovementInput(FVector(0.F, 1.0F, 0.F), Axis);
		if(CanRotate())
		{
			RotationVector.X = Axis;
			RotationVector.Y = 0; //Makes side facing always take precedence
		}
	}
	else
		Walking = false;
}

void APaper2DCharacter::ApplyPhysicalDamage(unsigned int Damage)
{
	if(!CharacterStats->isDead())
	{
		unsigned int TakenDmg = CharacterStats->ApplyPhysicalDamage(Damage);
		OnDamageTaken(TakenDmg);

		if(CharacterStats->isDead())
		{
			OnDeath();
		}
	}
}


void APaper2DCharacter::SetForwardAxis(float Axis)
{
	MovementVector.X = Axis;
}

void APaper2DCharacter::SetRightAxis(float Axis)
{
	MovementVector.Y = Axis;
}

void APaper2DCharacter::SetWalking(bool walking)
{
	Walking = walking;
}

void APaper2DCharacter::SetTicking(bool Ticking)
{
	PrimaryActorTick.bCanEverTick = Ticking;
}

bool APaper2DCharacter::CanMove()
{
	if(!Alive || Disabled)
		return false;

	return true;
}

bool APaper2DCharacter::CanAttack()
{
	if(!Disabled)
		return true;
	else
		return false;
}

bool APaper2DCharacter::CanRotate()
{
	if(!Disabled)
		return true;
	else
		return false;
}

bool APaper2DCharacter::isWalking()
{
	return Walking;
}

const FVector2D &APaper2DCharacter::GetRotationVector()
{
	return RotationVector;
}

void APaper2DCharacter::SetRotationVector(UPARAM(DisplayName = "Position")const FVector2D &Rotation)
{
	RotationVector = Rotation;
}

const FVector2D& APaper2DCharacter::SetAndReturnRotationVector(UPARAM(DisplayName = "Rotation")const FVector2D& Rotation)
{
	RotationVector = Rotation;
	return RotationVector;
}

bool APaper2DCharacter::isAlive()
{
	return Alive;
}

bool APaper2DCharacter::isFriendly()
{
	return Friendly;
}

void APaper2DCharacter::SetAttacking(UPARAM(DisplayName = "Attacking")bool attacking)
{
	Attacking = attacking;
	if(!Attacking)
		AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

bool APaper2DCharacter::isAttacking()
{
	return Attacking;
}

void APaper2DCharacter::StopCharacterLogic()
{
	GetMovementComponent()->StopActiveMovement();
	if(GetController()->IsA(AAIController::StaticClass())) //If this character is AI controlled, stop the logic.
	{
		AAIController* AIController = Cast<AAIController>(GetController());
		if (AIController != nullptr)
		{
			AIController->BrainComponent->StopLogic("Death");
		}
	}
}

void APaper2DCharacter::Disable()
{
	PrimaryActorTick.SetTickFunctionEnable(false);
	Disabled = true;
}

CharacterCommonStats *APaper2DCharacter::GetCharacterStats()
{
	return CharacterStats;
}

void APaper2DCharacter::OnDeath()
{
	Alive = false;
	StopCharacterLogic();

}

void APaper2DCharacter::OnDamageTaken(unsigned int DamageTaken)
{
	UDamageDisplayer* DamageText = CreateWidget<UDamageDisplayer>(GetWorld(), UDamageDisplayer::StaticClass());
	DamageText->LaunchDamageText(DamageTaken, (Friendly) ? FLinearColor(1.f, 0.f, 0.f, 1.f) : FLinearColor(1.f, 1.f, 1.f, 1.f), GetActorLocation());

	if(DamageSFX != nullptr)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DamageSFX, GetActorLocation());
}
