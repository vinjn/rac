// Copyright Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	Vehicle.cpp: AMyWheeledVehicle implementation
	TODO: Put description here
=============================================================================*/

#include "MyWheeledVehicle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "MyWheeledVehicleMovementComponent.h"
#include "MyWheeledVehicleMovementComponent4W.h"
#include "DisplayDebugHelpers.h"

FName AMyWheeledVehicle::VehicleMovementComponentName(TEXT("MovementComp"));
FName AMyWheeledVehicle::VehicleMeshComponentName(TEXT("VehicleMesh"));

PRAGMA_DISABLE_DEPRECATION_WARNINGS

AMyWheeledVehicle::AMyWheeledVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(VehicleMeshComponentName);
	Mesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
	Mesh->BodyInstance.bSimulatePhysics = true;
	Mesh->BodyInstance.bNotifyRigidBodyCollision = true;
	Mesh->BodyInstance.bUseCCD = true;
	Mesh->bBlendPhysics = true;
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCanEverAffectNavigation(false);
	RootComponent = Mesh;

	VehicleMovement = CreateDefaultSubobject<UMyWheeledVehicleMovementComponent, UMyWheeledVehicleMovementComponent4W>(VehicleMovementComponentName);
	VehicleMovement->SetIsReplicated(true); // Enable replication by default
	VehicleMovement->UpdatedComponent = Mesh;
}

void AMyWheeledVehicle::DisplayDebug(UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos)
{
	static FName NAME_Vehicle = FName(TEXT("Vehicle"));

	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);

	if (DebugDisplay.IsDisplayOn(NAME_Vehicle))
	{
#if WITH_PHYSX && PHYSICS_INTERFACE_PHYSX
		GetVehicleMovementComponent()->DrawDebug(Canvas, YL, YPos);
#endif // WITH_PHYSX
	}
}

class UMyWheeledVehicleMovementComponent* AMyWheeledVehicle::GetVehicleMovementComponent() const
{
	return VehicleMovement;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
