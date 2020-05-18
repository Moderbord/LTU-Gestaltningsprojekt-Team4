// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomTimerActor.generated.h"

UCLASS()
class MASKINSPELET_API ACustomTimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomTimerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FTimerHandle CreateTimer(int signal, float eventDelay);

	UFUNCTION(BlueprintImplementableEvent)
	void LaunchEvent(int signal);
};
