// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "Runtime/Engine/Classes/Engine/Font.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "DamageDisplayer.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API UDamageDisplayer : public UUserWidget, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UDamageDisplayer(const FObjectInitializer& ObjectInitializer);
	
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	//Sends the amount of damage given flying in a parabolic curve.
	void LaunchDamageText(unsigned int Damage, const FLinearColor& Color, const FVector& WorldSpace);

	//Sends a "miss" text flying in a parabolic curve.
	void LaunchMissText(const FLinearColor& Color, const FVector& WorldSpace);

private:
	bool Ticks; //Set this to true to enable ticking.

	const float NumSecExpires = 1.0f; //Number of seconds until the text expires.
	float TicksPassed; //Ticks that have passed since ticking started.

	float ParabolaConstant; //The parabola constant to calculate the path of the damage text. Formula: y = ParabolaConstant*x^2 + ParabolaMagnitude*x.
	float ParabolaMagnitude; //The magnitude constant to calculate the path of the damage text. Is randomized to either 8 or -8.
	float ParabolaNumXUnits; //The number of x units to travel until finishing the parabola and fading out.
	float ParabolaCurrentX; //The current x location we are on the parabolic function.

	//Creates a random parabola function.
	void RandomizeParabola();

	//The world space location of this damage displayer.
	FVector WorldSpaceLocation;

	//The font used to display damage.
	static FSlateFontInfo *FInfo;

	//The typeface needed to create the font info.
	static UFont *Typeface;

	//The damage text to be displayed.
	UPROPERTY(EditAnywhere)
	UTextBlock *DamageText;

};
