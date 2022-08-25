// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SphereDestroyerHUD.generated.h"

UCLASS()
class ASphereDestroyerHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASphereDestroyerHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

