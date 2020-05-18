// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTimerActor.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values
ACustomTimerActor::ACustomTimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomTimerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomTimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FTimerHandle ACustomTimerActor::CreateTimer(int signal, float eventDelay)
{
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	//Binding the function with specific values
	TimerDel.BindUFunction(this, FName("LaunchEvent"), signal);
	//Calling MyUsefulFunction after 5 seconds without looping
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, eventDelay, false);

	return TimerHandle;
}
