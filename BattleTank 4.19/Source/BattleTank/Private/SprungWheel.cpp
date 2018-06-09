// Copyright The Raw Studio

#include "BattleTank.h"
#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MassWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstraint"));
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	
	SetRootComponent(MassWheelConstraint);
	Wheel->SetupAttachment(MassWheelConstraint);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (!GetAttachParentActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL"));
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

