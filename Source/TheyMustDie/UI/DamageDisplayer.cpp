// ©Kris and Tashhhh 2023

#include "DamageDisplayer.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include <math.h>

FSlateFontInfo* UDamageDisplayer::FInfo = nullptr;
UFont* UDamageDisplayer::Typeface = nullptr;

UDamageDisplayer::UDamageDisplayer(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer), TicksPassed(0.f), DamageText(nullptr), ParabolaCurrentX(0.f), ParabolaConstant(-0.1f), ParabolaMagnitude(4.f), ParabolaNumXUnits(49.f)
{
	if(FInfo == nullptr || Typeface == nullptr)
	{
		static ConstructorHelpers::FObjectFinder<UFont> PixelFont(TEXT("Font'/Game/UI/Pixeled_Font.Pixeled_Font'"));
		/*/if (PixelFont.Succeeded() == false)
			DebugMessage("Failed to load pixel font");
		else
		{*/
		if(PixelFont.Succeeded())
		{
			Typeface = PixelFont.Object;
			FInfo = new FSlateFontInfo();
			FInfo->FontObject = Typeface;
			FInfo->Size = 15;
			FFontOutlineSettings Outline;
			Outline.OutlineColor = FLinearColor(0.f, 0.f, 0.f, 1.0f);
			Outline.OutlineSize = 2;
			FInfo->OutlineSettings = Outline;
		}
	}

	Ticks = false; //Start ticking after data has been added.
	SetVisibility(ESlateVisibility::Visible);
}

void UDamageDisplayer::RandomizeParabola()
{
	int32 RandInt = FMath::RandRange(0, 4);
	if (RandInt == 0)
	{
		bool Positive = FMath::RandBool();
		ParabolaMagnitude = Positive ? 4.f : -4.f;
		ParabolaConstant = -0.1f;
		ParabolaNumXUnits = 49.f;
		return;
	}
	else if (RandInt == 1)
	{
		bool Positive = FMath::RandBool();
		ParabolaMagnitude = Positive ? 3.75f : -3.75f;
		ParabolaConstant = -0.0875f;
		ParabolaNumXUnits = 52.f;
		return;
	}
	else if (RandInt == 2)
	{
		bool Positive = FMath::RandBool();
		ParabolaMagnitude = Positive ? 4.85f : -4.85f;
		ParabolaConstant = -0.15f;
		ParabolaNumXUnits = 39.f;
		return;
	}
	else if (RandInt == 3)
	{
		bool Positive = FMath::RandBool();
		ParabolaMagnitude = Positive ? 3.5f : -3.5f;
		ParabolaConstant = -0.077f;
		ParabolaNumXUnits = 55.f;
		return;
	}
	else if (RandInt == 4)
	{
		bool Positive = FMath::RandBool();
		ParabolaMagnitude = Positive ? 4.5f : -4.5f;
		ParabolaConstant = -0.1233f;
		ParabolaNumXUnits = 44.f;
	}
}

void UDamageDisplayer::LaunchDamageText(unsigned int Damage, const FLinearColor& Color, const FVector& WorldSpace)
{
	WorldSpaceLocation = WorldSpace;
	if (WidgetTree != nullptr)
	{
		DamageText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		DamageText->SetFont(*FInfo);
		DamageText->SetJustification(ETextJustify::Center);
		if (GetRootWidget() == nullptr)
		{
			UCanvasPanel* Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
			Root->AddChild(DamageText);
			WidgetTree->RootWidget = Root;
		}
	}
	else
		return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WorldSpaceLocation, ScreenPosition);
	RandomizeParabola(); //Generates a random parabola out of a number of permutations to move the damage text with.
	SetPositionInViewport(ScreenPosition); //Sets the position of the widget to screen position from world coordinates.
	SetAlignmentInViewport(FVector2D(0.5f, 0.f));
	DamageText->SetColorAndOpacity(Color);
	DamageText->Text = FText(FText::FromString(FString(FString::FromInt(Damage))));
	Ticks = true;

	AddToViewport(999); //High priority ZOrder.
}

void UDamageDisplayer::LaunchMissText(const FLinearColor& Color, const FVector& WorldSpace)
{
	WorldSpaceLocation = WorldSpace;
	if (WidgetTree != nullptr)
	{
		DamageText = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
		DamageText->SetFont(*FInfo);
		DamageText->SetJustification(ETextJustify::Center);
		if (GetRootWidget() == nullptr)
		{
			UCanvasPanel* Root = WidgetTree->ConstructWidget<UCanvasPanel>(UCanvasPanel::StaticClass());
			Root->AddChild(DamageText);
			WidgetTree->RootWidget = Root;
		}
	}
	else
		return;

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WorldSpaceLocation, ScreenPosition);
	RandomizeParabola(); //Generates a random parabola out of a number of permutations to move the damage text with.
	SetPositionInViewport(ScreenPosition); //Sets the position of the widget to screen position from world coordinates.
	SetAlignmentInViewport(FVector2D(0.5f, 0.f));
	DamageText->SetColorAndOpacity(Color);
	DamageText->Text = FText(FText::FromString(FString("Miss")));
	Ticks = true;

	AddToViewport(999); //High priority ZOrder.
}

void UDamageDisplayer::Tick(float DeltaTime)
{
	FLinearColor Color = DamageText->ColorAndOpacity.GetSpecifiedColor();
	float Opacity = Color.A - ((1 / NumSecExpires) * DeltaTime);
	Color.A = Opacity;
	DamageText->SetColorAndOpacity(Color);
	FSlateFontInfo NewFont = DamageText->Font;
	NewFont.OutlineSettings.OutlineColor = FLinearColor(0.f, 0.f, 0.f, Opacity);
	DamageText->SetFont(NewFont);

	if (ParabolaMagnitude >= 0) //Move X in positive direction if it's a positive magnitude.
		ParabolaCurrentX += (ParabolaNumXUnits / NumSecExpires) * DeltaTime;
	else //Move X in negative direction if it's a negative magnitude.
		ParabolaCurrentX -= (ParabolaNumXUnits / NumSecExpires) * DeltaTime;

	float ParabolaCurrentY = -(ParabolaConstant * pow(ParabolaCurrentX, 2) + (ParabolaMagnitude * ParabolaCurrentX));
	FVector2D ScreenSpaceOffset(ParabolaCurrentX, ParabolaCurrentY);

	FVector2D ScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), WorldSpaceLocation, ScreenPosition);
	ScreenPosition += ScreenSpaceOffset;
	SetPositionInViewport(ScreenPosition); //Updates the screen space location of this widget in case the player has moved or rotated the screen.

	TicksPassed += DeltaTime;
	if (TicksPassed >= NumSecExpires)
	{
		Ticks = false;
		RemoveFromViewport();
	}
}

bool UDamageDisplayer::IsTickable() const
{
	return Ticks;
}

TStatId UDamageDisplayer::GetStatId() const
{
	return Super::GetStatID();
}