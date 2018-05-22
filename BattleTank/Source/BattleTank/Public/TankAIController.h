// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:

	ATank* GetPlayerTank() const;

	ATank* GetControlledTank() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
