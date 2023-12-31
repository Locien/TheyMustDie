// ©Kris and Tashhhh 2023

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "Engine/GameInstance.h"
#include "TheyMustDieGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEYMUSTDIE_API UTheyMustDieGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTheyMustDieGameInstance();

protected:
	//The current BGM
	UPROPERTY(EditDefaultsOnly, Category = "BGM")
	USoundCue *BGM;

	//Called once when the game starts
	void OnStart() override;
	
};
