// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/Pawn.h"
#include "MyWheeledVehicle.generated.h"

class FDebugDisplayInfo;

/**
 * WheeledVehicle is the base wheeled vehicle pawn actor.
 * By default it uses UMyWheeledVehicleMovementComponent4W for its simulation, but this can be overridden by inheriting from the class and modifying its constructor like so:
 * Super(ObjectInitializer.SetDefaultSubobjectClass<UMyMovement>(VehicleMovementComponentName))
 * Where UMyMovement is the new movement type that inherits from UMyWheeledVehicleMovementComponent
 * 
 * @see https://docs.unrealengine.com/latest/INT/Engine/Physics/Vehicles/VehicleUserGuide/
 * @see UMyWheeledVehicleMovementComponent4W
 */

UCLASS(abstract, config=Game, BlueprintType)
class  AMyWheeledVehicle : public APawn
{
	GENERATED_UCLASS_BODY()

private:
	/**  The main skeletal mesh associated with this Vehicle */
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	/** vehicle simulation component */
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMyWheeledVehicleMovementComponent* VehicleMovement;
public:

	/** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
	static FName VehicleMeshComponentName;

	/** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
	static FName VehicleMovementComponentName;

	/** Util to get the wheeled vehicle movement component */
	class UMyWheeledVehicleMovementComponent* GetVehicleMovementComponent() const;

	//~ Begin AActor Interface
	virtual void DisplayDebug(class UCanvas* Canvas, const FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos) override;
	//~ End Actor Interface

	/** Returns Mesh subobject **/
	class USkeletalMeshComponent* GetMesh() const { return Mesh; }
	/** Returns VehicleMovement subobject **/
	class UMyWheeledVehicleMovementComponent* GetVehicleMovement() const { return VehicleMovement; }
};
