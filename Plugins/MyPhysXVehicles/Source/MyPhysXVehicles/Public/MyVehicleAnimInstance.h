// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
/**
 *
 */

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimInstanceProxy.h"
#include "MyVehicleAnimInstance.generated.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UMyWheeledVehicleMovementComponent;

struct FMyWheelAnimData
{
	FName BoneName;
	FRotator RotOffset;
	FVector LocOffset;
};

 /** Proxy override for this UAnimInstance-derived class */
struct UE_DEPRECATED(4.26, "PhysX is deprecated. Use the FVehicleAnimationInstanceProxy from the ChaosVehiclePhysics Plugin.") FMyVehicleAnimInstanceProxy;
USTRUCT()
struct  FMyVehicleAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

	FMyVehicleAnimInstanceProxy()
		: FAnimInstanceProxy()
	{
	}

	FMyVehicleAnimInstanceProxy(UAnimInstance* Instance)
		: FAnimInstanceProxy(Instance)
	{
	}

public:

	void SetWheeledVehicleMovementComponent(const UMyWheeledVehicleMovementComponent* InWheeledVehicleMovementComponent);

	/** FAnimInstanceProxy interface begin*/
	virtual void PreUpdate(UAnimInstance* InAnimInstance, float DeltaSeconds) override;
	/** FAnimInstanceProxy interface end*/

	const TArray<FMyWheelAnimData>& GetWheelAnimData() const
	{
		return WheelInstances;
	}

private:
	TArray<FMyWheelAnimData> WheelInstances;
};

class UE_DEPRECATED(4.26, "PhysX is deprecated. Use the UVehicleAnimationInstance from the ChaosVehiclePhysics Plugin.") UMyVehicleAnimInstance;
UCLASS(transient)
class  UMyVehicleAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

	/** Makes a montage jump to the end of a named section. */
	UFUNCTION(BlueprintCallable, Category="Animation")
	class AMyWheeledVehicle * GetVehicle();

public:
	TArray<FMyWheelAnimData> WheelData;

public:
	
	void SetWheeledVehicleMovementComponent(const UMyWheeledVehicleMovementComponent* InWheeledVehicleMovementComponent)
	{
		WheeledVehicleMovementComponent = InWheeledVehicleMovementComponent;
		AnimInstanceProxy.SetWheeledVehicleMovementComponent(InWheeledVehicleMovementComponent);
	}

	const UMyWheeledVehicleMovementComponent* GetWheeledVehicleMovementComponent() const
	{
		return WheeledVehicleMovementComponent;
	}

private:
	/** UAnimInstance interface begin*/
	virtual void NativeInitializeAnimation() override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;
	/** UAnimInstance interface end*/

	FMyVehicleAnimInstanceProxy AnimInstanceProxy;
	
	UPROPERTY(transient)
	const UMyWheeledVehicleMovementComponent* WheeledVehicleMovementComponent;

};

PRAGMA_ENABLE_DEPRECATION_WARNINGS


