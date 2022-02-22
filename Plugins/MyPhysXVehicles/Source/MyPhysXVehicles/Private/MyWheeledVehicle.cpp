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
#include "Engine/Canvas.h"

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
	Super::DisplayDebug(Canvas, DebugDisplay, YL, YPos);
	
	UFont* RenderFont = GEngine->GetLargeFont();

	GetVehicleMovementComponent()->DrawDebug(Canvas, YL, YPos);
	if (DebugMode == Mode_DrawDebugGraphs)
		GetVehicleMovementComponent()->DrawDebugGraphs(Canvas, YL, YPos);
	else if (DebugMode == Mode_DrawDebugLine)
	{
		Canvas->SetDrawColor(FColor::Red);
		Canvas->DrawText(RenderFont, "Tire Load and Slips", 4, YPos);
		GetVehicleMovementComponent()->DrawDebugLines();
	}
	else if (DebugMode == Mode_DrawTireForces)
	{
		Canvas->SetDrawColor(FColor::Red);
		Canvas->DrawText(RenderFont, "Tire Forces", 4, YPos);
		GetVehicleMovementComponent()->DrawTireForces();
	}
}

class UMyWheeledVehicleMovementComponent* AMyWheeledVehicle::GetVehicleMovementComponent() const
{
	return VehicleMovement;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
