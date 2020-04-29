// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FP_HUD.generated.h"

/**
 * 
 */
UCLASS()
class MASKINSPELET_API AFP_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AFP_HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};
