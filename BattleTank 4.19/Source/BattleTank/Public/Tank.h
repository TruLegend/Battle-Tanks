// Copyright The Raw Studio.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h" // Put new includes above this

UENUM()
enum class EHealthColour : uint8
{
	ALLY,
	ENEMY
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called by the engine when actor is damaged
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Returns current health as a percentage
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EHealthColour HealthColour = EHealthColour::ALLY;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	int32 DamageToApply = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	int32 CurrentHealth; // Initialised in begin play
};
