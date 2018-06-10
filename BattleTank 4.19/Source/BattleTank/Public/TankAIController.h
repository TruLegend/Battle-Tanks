// Copyright The Raw Studio.
#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

protected:
	// How close can the AI tank get in cm
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 10000; // 100m

private:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	// When the AI Controller posseses a tank, this method gets called
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 6000;

	UPROPERTY(VisibleAnywhere, Category = "Player")
		int32 AITanks = 0;
};
