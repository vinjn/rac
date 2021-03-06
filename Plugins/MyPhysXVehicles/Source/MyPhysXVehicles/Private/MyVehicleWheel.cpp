// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyVehicleWheel.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "PhysxUserData.h"
#include "Engine/StaticMesh.h"
#include "Vehicles/TireType.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyTireConfig.h"
#include "MyPhysXVehicleManager.h"
#include "PhysXPublic.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

UMyVehicleWheel::UMyVehicleWheel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CollisionMeshObj(TEXT("/Engine/EngineMeshes/Cylinder"));
	CollisionMesh = CollisionMeshObj.Object;

	ShapeRadius = 30.0f;
	ShapeWidth = 10.0f;
	bAutoAdjustCollisionSize = true;
	Mass = 20.0f;
	bAffectedByHandbrake = true;
	SteerAngle = 70.0f;
	MaxBrakeTorque = 1500.f;
	MaxHandBrakeTorque = 3000.f;
	DampingRate = 0.25f;
	LatStiffMaxLoad = 2.0f;
	LatStiffValue = 17.0f;
	LongStiffValue = 1000.0f;
	SuspensionForceOffset = 0.0f;
	SuspensionMaxRaise = 10.0f;
	SuspensionMaxDrop = 10.0f;
	SuspensionNaturalFrequency = 7.0f;
	SuspensionDampingRatio = 1.0f;
	SweepType = EMyWheelSweepType::SimplePlusComplex;
}

#if WITH_PHYSX_VEHICLES
FMyPhysXVehicleManager* UMyVehicleWheel::GetVehicleManager() const
{
	UWorld* World = GEngine->GetWorldFromContextObject(VehicleSim, EGetWorldErrorMode::LogAndReturnNull);
	return World ? FMyPhysXVehicleManager::GetVehicleManagerFromScene(World->GetPhysicsScene()) : nullptr;
}
#endif // WITH_PHYSX

float UMyVehicleWheel::GetSteerAngle() const
{
#if WITH_PHYSX_VEHICLES
	if (FMyPhysXVehicleManager* VehicleManager = GetVehicleManager())
	{
		SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());
		return FMath::RadiansToDegrees(VehicleManager->GetWheelsStates_AssumesLocked(VehicleSim)[WheelIndex].steerAngle);
	}
#endif // WITH_PHYSX
	return 0.0f;
}

float UMyVehicleWheel::GetRotationAngle() const
{
#if WITH_PHYSX_VEHICLES
	if (FMyPhysXVehicleManager* VehicleManager = GetVehicleManager())
	{
		SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

		float RotationAngle = -1.0f * FMath::RadiansToDegrees(VehicleSim->PVehicle->mWheelsDynData.getWheelRotationAngle(WheelIndex));
		ensure(!FMath::IsNaN(RotationAngle));
		return RotationAngle;
	}
#endif // WITH_PHYSX
	return 0.0f;
}

float UMyVehicleWheel::GetSuspensionOffset() const
{
#if WITH_PHYSX_VEHICLES
	if (FMyPhysXVehicleManager* VehicleManager = GetVehicleManager())
	{
		SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

		return VehicleManager->GetWheelsStates_AssumesLocked(VehicleSim)[WheelIndex].suspJounce;
	}
#endif // WITH_PHYSX
	return 0.0f;
}

bool UMyVehicleWheel::IsInAir() const
{
#if WITH_PHYSX_VEHICLES
	if (FMyPhysXVehicleManager* VehicleManager = GetVehicleManager())
	{
		SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

		return VehicleManager->GetWheelsStates_AssumesLocked(VehicleSim)[WheelIndex].isInAir;
	}
#endif // WITH_PHYSX
	return false;
}

void UMyVehicleWheel::Init( UMyWheeledVehicleMovementComponent* InVehicleSim, int32 InWheelIndex )
{
	check(InVehicleSim);
	check(InVehicleSim->Wheels.IsValidIndex(InWheelIndex));

	VehicleSim = InVehicleSim;
	WheelIndex = InWheelIndex;

#if WITH_PHYSX_VEHICLES
	WheelShape = NULL;

	FMyPhysXVehicleManager* VehicleManager = FMyPhysXVehicleManager::GetVehicleManagerFromScene(VehicleSim->GetWorld()->GetPhysicsScene());
	SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

	const int32 WheelShapeIdx = VehicleSim->PVehicle->mWheelsSimData.getWheelShapeMapping( WheelIndex );
	check(WheelShapeIdx >= 0);

	VehicleSim->PVehicle->getRigidDynamicActor()->getShapes( &WheelShape, 1, WheelShapeIdx );
	check(WheelShape);
#endif // WITH_PHYSX

	Location = GetPhysicsLocation();
	OldLocation = Location;
}

void UMyVehicleWheel::Shutdown()
{
#if WITH_PHYSX_VEHICLES
	WheelShape = NULL;
#endif // WITH_PHYSX
}

FMyWheelSetup& UMyVehicleWheel::GetWheelSetup()
{
	return VehicleSim->WheelSetups[WheelIndex];
}

void UMyVehicleWheel::Tick( float DeltaTime )
{
	OldLocation = Location;
	Location = GetPhysicsLocation();
	Velocity = ( Location - OldLocation ) / DeltaTime;
}

FVector UMyVehicleWheel::GetPhysicsLocation()
{
#if WITH_PHYSX_VEHICLES
	if ( WheelShape )
	{
		if (FMyPhysXVehicleManager* VehicleManager = GetVehicleManager())
		{
			SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

			PxVec3 PLocation = VehicleSim->PVehicle->getRigidDynamicActor()->getGlobalPose().transform(WheelShape->getLocalPose()).p;
			return P2UVector(PLocation);
		}
	}
#endif // WITH_PHYSX
	return FVector::ZeroVector;
}

#if WITH_EDITOR

void UMyVehicleWheel::PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent )
{
	Super::PostEditChangeProperty( PropertyChangedEvent );

#if WITH_PHYSX_VEHICLES
	// Trigger a runtime rebuild of the PhysX vehicle
	FMyPhysXVehicleManager::VehicleSetupTag++;
#endif // WITH_PHYSX
}

#endif //WITH_EDITOR


UPhysicalMaterial* UMyVehicleWheel::GetContactSurfaceMaterial()
{
	UPhysicalMaterial* PhysMaterial = NULL;

#if WITH_PHYSX_VEHICLES
	FMyPhysXVehicleManager* VehicleManager = FMyPhysXVehicleManager::GetVehicleManagerFromScene(VehicleSim->GetWorld()->GetPhysicsScene());
	SCOPED_SCENE_READ_LOCK(VehicleManager->GetScene());

	const PxMaterial* ContactSurface = VehicleManager->GetWheelsStates_AssumesLocked(VehicleSim)[WheelIndex].tireSurfaceMaterial;
	if (ContactSurface)
	{
		PhysMaterial = FPhysxUserData::Get<UPhysicalMaterial>(ContactSurface->userData);
	}
#endif // WITH_PHYSX

	return PhysMaterial;
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS

