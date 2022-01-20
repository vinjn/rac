// Copyright Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	UMyVehicleAnimInstance.cpp: Single Node Tree Instance 
	Only plays one animation at a time. 
=============================================================================*/ 

#include "MyVehicleAnimInstance.h"
#include "MyWheeledVehicleMovementComponent.h"
#include "MyWheeledVehicle.h"
#include "AnimationRuntime.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

/////////////////////////////////////////////////////
// UMyVehicleAnimInstance
/////////////////////////////////////////////////////

UMyVehicleAnimInstance::UMyVehicleAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

class AMyWheeledVehicle * UMyVehicleAnimInstance::GetVehicle()
{
	return Cast<AMyWheeledVehicle> (GetOwningActor());
}

void UMyVehicleAnimInstance::NativeInitializeAnimation()
{
	// Find a wheeled movement component
	if (AActor* Actor = GetOwningActor())
	{
		if (UMyWheeledVehicleMovementComponent* FoundWheeledVehicleMovementComponent = Actor->FindComponentByClass<UMyWheeledVehicleMovementComponent>())
		{
			SetWheeledVehicleMovementComponent(FoundWheeledVehicleMovementComponent);
		}
	}
}

FAnimInstanceProxy* UMyVehicleAnimInstance::CreateAnimInstanceProxy()
{
	return &AnimInstanceProxy;
}

void UMyVehicleAnimInstance::DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy)
{
}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
//// PROXY ///

void FMyVehicleAnimInstanceProxy::SetWheeledVehicleMovementComponent(const UMyWheeledVehicleMovementComponent* InWheeledVehicleMovementComponent)
{
	const UMyWheeledVehicleMovementComponent* WheeledVehicleMovementComponent = InWheeledVehicleMovementComponent;

	//initialize wheel data
	const int32 NumOfwheels = WheeledVehicleMovementComponent->WheelSetups.Num();
	WheelInstances.Empty(NumOfwheels);
	if (NumOfwheels > 0)
	{
		WheelInstances.AddZeroed(NumOfwheels);
		// now add wheel data
		for (int32 WheelIndex = 0; WheelIndex<WheelInstances.Num(); ++WheelIndex)
		{
			FMyWheelAnimData& WheelInstance = WheelInstances[WheelIndex];
			const FMyWheelSetup& WheelSetup = WheeledVehicleMovementComponent->WheelSetups[WheelIndex];

			// set data
			WheelInstance.BoneName = WheelSetup.BoneName;
			WheelInstance.LocOffset = FVector::ZeroVector;
			WheelInstance.RotOffset = FRotator::ZeroRotator;
		}
	}
}

void FMyVehicleAnimInstanceProxy::PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(InAnimInstance, DeltaSeconds);

	const UMyVehicleAnimInstance* VehicleAnimInstance = CastChecked<UMyVehicleAnimInstance>(InAnimInstance);
	if(const UMyWheeledVehicleMovementComponent* WheeledVehicleMovementComponent = VehicleAnimInstance->GetWheeledVehicleMovementComponent())
	{
		for (int32 WheelIndex = 0; WheelIndex < WheelInstances.Num(); ++ WheelIndex)
		{
			FMyWheelAnimData& WheelInstance = WheelInstances[WheelIndex];
			if (WheeledVehicleMovementComponent->Wheels.IsValidIndex(WheelIndex))
			{
				if (const UMyVehicleWheel* VehicleWheel = WheeledVehicleMovementComponent->Wheels[WheelIndex])
				{
					WheelInstance.RotOffset.Pitch = VehicleWheel->GetRotationAngle();
					WheelInstance.RotOffset.Yaw = VehicleWheel->GetSteerAngle();
					WheelInstance.RotOffset.Roll = 0.f;

					WheelInstance.LocOffset.X = 0.f;
					WheelInstance.LocOffset.Y = 0.f;
					WheelInstance.LocOffset.Z = VehicleWheel->GetSuspensionOffset();
				}
			}
		}
	}
}

PRAGMA_ENABLE_DEPRECATION_WARNINGS
