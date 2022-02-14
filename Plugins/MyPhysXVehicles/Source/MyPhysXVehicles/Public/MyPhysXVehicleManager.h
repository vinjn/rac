// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MyWheeledVehicleMovementComponent.h"
#include "PhysicsPublic.h"
#include "PhysXIncludes.h"

class UMyTireConfig;
class UMyWheeledVehicleMovementComponent;
class FPhysScene_PhysX;

#include "PxVehicleSuspWheelTire4.h"
#include "PxVehicleComponents.h"
#include "PxVehicleDrive.h"
#include "PxVehicleDrive4W.h"
#include "PxVehicleDriveTank.h"
#include "PxVehicleSDK.h"
#include "PxVehicleShaders.h"
#include "PxVehicleTireFriction.h"
#include "PxVehicleUpdate.h"
#include "PxVehicleUtilControl.h"
#include "PxVehicleUtilSetup.h"
#include "PxVehicleUtilTelemetry.h"
#include "PxVehicleWheels.h"
#include "PxVehicleNoDrive.h"
#include "PxVehicleDriveNW.h"

DECLARE_LOG_CATEGORY_EXTERN(LogVehicles, Log, All);

PRAGMA_DISABLE_DEPRECATION_WARNINGS

#if WITH_PHYSX_VEHICLES

/**
 * Manages vehicles and tire surface data for all scenes
 */

class  FMyPhysXVehicleManager
{
public:

	// Updated when vehicles need to recreate their physics state.
	// Used when designer tweaks values while the game is running.
	static uint32											VehicleSetupTag;

	FMyPhysXVehicleManager(FPhysScene* PhysScene);
	~FMyPhysXVehicleManager();

	/**
	 * Refresh the tire friction pairs
	 */
	static void UpdateTireFrictionTable();

	/**
	 * Register a PhysX vehicle for processing
	 */
	void AddVehicle( TWeakObjectPtr<UMyWheeledVehicleMovementComponent> Vehicle );

	/**
	 * Unregister a PhysX vehicle from processing
	 */
	void RemoveVehicle( TWeakObjectPtr<UMyWheeledVehicleMovementComponent> Vehicle );

	/**
	 * Set the vehicle that we want to record telemetry data for
	 */
	void SetRecordTelemetry( TWeakObjectPtr<UMyWheeledVehicleMovementComponent> Vehicle, bool bRecord );

	/**
	 * Get the updated telemetry data
	 */
	PxVehicleTelemetryData* GetTelemetryData_AssumesLocked();
	
	/**
	 * Get a vehicle's wheels states, such as isInAir, suspJounce, contactPoints, etc
	 */
	PxWheelQueryResult* GetWheelsStates_AssumesLocked(TWeakObjectPtr<const UMyWheeledVehicleMovementComponent> Vehicle);

	/**
	 * Update vehicle data before the scene simulates
	 */
	void Update(FPhysScene* PhysScene, float DeltaTime);
	
	/**
	 * Update vehicle tuning and other state such as input */
	void PreTick(FPhysScene* PhysScene, float DeltaTime);

	/** Detach this vehicle manager from a FPhysScene (remove delegates, remove from map etc) */
	void DetachFromPhysScene(FPhysScene* PhysScene);

	PxScene* GetScene() const { return Scene; }



	/** Find a vehicle manager from an FPhysScene */
	static FMyPhysXVehicleManager* GetVehicleManagerFromScene(FPhysScene* PhysScene);

	/** Gets a transient default TireConfig object */
	static UMyTireConfig* GetDefaultTireConfig();

private:

	// True if the tire friction table needs to be updated
	static bool													bUpdateTireFrictionTable;

	// Friction from combinations of tire and surface types.
	static PxVehicleDrivableSurfaceToTireFrictionPairs*			SurfaceTirePairs;

	/** Map of physics scenes to corresponding vehicle manager */
	static TMap<FPhysScene*, FMyPhysXVehicleManager*>		        SceneToVehicleManagerMap;


	// The scene we belong to
	PxScene*													Scene;

	// All instanced vehicles
	TArray<TWeakObjectPtr<UMyWheeledVehicleMovementComponent>>	Vehicles;

	// All instanced PhysX vehicles
	TArray<PxVehicleWheels*>									PVehicles;

	// Store each vehicle's wheels' states like isInAir, suspJounce, contactPoints, etc
	TArray<PxVehicleWheelQueryResult>							PVehiclesWheelsStates;

	// Scene query results for each wheel for each vehicle
	TArray<PxRaycastQueryResult>								WheelQueryResults;

	// Scene raycast hits for each wheel for each vehicle
	TArray<PxRaycastHit>										WheelHitResults;

	// Batch query for the wheel suspension raycasts
	PxBatchQuery*												WheelRaycastBatchQuery;

	FDelegateHandle OnPhysScenePreTickHandle;
	FDelegateHandle OnPhysSceneStepHandle;


	/**
	 * Refresh the tire friction pairs
	 */
	void UpdateTireFrictionTableInternal();

	/**
	 * Reallocate the WheelRaycastBatchQuery if our number of wheels has increased
	 */
	void SetUpBatchedSceneQuery();

	/**
	 * Update all vehicles without telemetry
	 */
	void UpdateVehicles( float DeltaTime );

	/**
	 * Get the gravity for our phys scene
	 */
	PxVec3 GetSceneGravity_AssumesLocked();

#if PX_DEBUG_VEHICLE_ON

	PxVehicleTelemetryData*				TelemetryData4W;

	PxVehicleWheels*					TelemetryVehicle;

	/**
	 * Init telemetry data
	 */
	void SetupTelemetryData();

	/**
	 * Update the telemetry vehicle and then all other vehicles
	 */
	void UpdateVehiclesWithTelemetry( float DeltaTime );

#endif //PX_DEBUG_VEHICLE_ON
};

#endif // WITH_PHYSX

PRAGMA_ENABLE_DEPRECATION_WARNINGS