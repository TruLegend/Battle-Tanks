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

		if (!ensure(PossessedTank)) { return; }
	
		// TODO: Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

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
	UE_LOG(LogTemp, Warning, TEXT("AI Tank Died/De-possessed"));
}