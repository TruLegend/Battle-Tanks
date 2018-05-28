// Copyright The Raw Studio.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If out of ammo
	if (Ammo <= 0)
	{
		Ammo = 0;
		FiringState = EFiringState::EMPTY;
	}
	// If we have reloaded
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::RELOADING;
	}
	// If we are aiming
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::AIMING;
	}
	// If we are locked
	else
	{
		FiringState = EFiringState::LOCKED;
	}

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) {return;} // If we don't have a barrel, get out.
	if (!ensure(Turret)) {return;} // If we don't have a turret, get out.

	FVector OutLaunchVelocity; // Out parameter
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile")); // Start location
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	// If no solution found, do nothing.
}

void UTankAimingComponent::Fire()
{
	// If not reloading, then fire
	if (FiringState == EFiringState::AIMING || FiringState == EFiringState::LOCKED)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		// Spawn a projectile at the socket location of the barrel
		auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammo -= 1;
	}
	// If ammunition is empty OR If we are reloading
	else if (FiringState == EFiringState::RELOADING || FiringState == EFiringState::EMPTY)
	{
		// Don't fire
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel || Turret)) { return; }

	// Work out the differnce between the current barrel location and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the shortest way
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
	{
		DeltaRotator.Yaw = -AimAsRotator.Yaw;
	}

	Turret->Rotate(DeltaRotator.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	if (!BarrelForward.Equals(AimDirection, 0.01f))
	{
		return true;
	}
	else
	{
		return false;
	}

}
