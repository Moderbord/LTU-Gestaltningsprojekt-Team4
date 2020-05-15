// Fill out your copyright notice in the Description page of Project Settings.


#include "FP_GameModeBase.h"
#include "FP_HUD.h"
#include "FP_Character.h"
#include "UObject/ConstructorHelpers.h"

AFP_GameModeBase::AFP_GameModeBase()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Source/Character/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
