// Copyright Epic Games, Inc. All Rights Reserved.

#include "SphereDestroyerGameMode.h"
#include "SphereDestroyerHUD.h"
#include "SphereDestroyerCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"


#include "Kismet/GameplayStatics.h" 

#include "Target.h"
#include "SphereDestroyerCharacter.h"
ASphereDestroyerGameMode::ASphereDestroyerGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASphereDestroyerHUD::StaticClass();

}