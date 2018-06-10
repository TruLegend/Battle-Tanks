// Copyright The Raw Studio.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // So we can implement on death


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (!PossessedTank) { return; }

		PossessedTank->HealthColour = EHealthColour::ENEMY;
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!(PlayerTank && ControlledTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	if (!PlayerTank) { return; }

	// Aim towards the player
	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComponent->GetFiringState() == EFiringState::LOCKED)
	{
		TankAimingComponent->Fire(); // TODO: Don't fire every frame/limit fire rate
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}