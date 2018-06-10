// Copyright The Raw Studio.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankAIController.h"
#include "TankPlayerController.generated.h" // Must be the last include

// Forward Declaration
class UTankAimingComponent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Player")
		int32 GetPlayerTanks() const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimComRef);

private:
	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world.
	void AimTowardsCrosshair();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	// When the AI Controller posseses a tank, this method gets called
	virtual void SetPawn(APawn* InPawn) override;

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UFUNCTION()
		void OnTankDeath();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float CrossHairLocationX = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float CrossHairLocationY = 0.33333;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float LineTraceRange = 1000000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 10000;

	UPROPERTY(VisibleAnywhere, Category = "Player")
		int32 PlayerTanks = 0;
};
