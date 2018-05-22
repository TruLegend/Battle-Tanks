// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO: Prevent double-speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

	//TODO: Prevent double-speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	auto MoveVelocityString = MoveVelocity.GetSafeNormal().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring at %s"), *TankName, *MoveVelocityString);
}

